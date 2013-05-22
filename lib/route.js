"use strict";

var util = require('util');
var events = require('events');
var url = require('url');

var Internal = require('./internal');
var Define = require('./define');

var Route = module.exports = function() {
	var self = this;

	Internal.on('request', function(protocol) {
		self.requestHandler(protocol);
	});
};

util.inherits(Route, events.EventEmitter);

Route.prototype.requestHandler = function(protocol) {
	var self = this;

	var messageObject = protocol.messageObject;

	// Request Object
	var req = url.parse(protocol.url);

	// Response Object
	var res = {};
	res.set = function(key, value) {
		if (key == 'Content-Type')
			Internal.setMIMEType(messageObject, value);
	};

	res.status = function(code) {
		Internal.setStatus(messageObject, code);
	};

	res.send = function(data) {
		Internal.setContent(messageObject, data);
	};

	res.end = function(data) {
		if (data)
			Internal.setContent(messageObject, data);

		Internal.runCallback(messageObject);
	};

	self.emit('request', req, res);
};
