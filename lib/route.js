"use strict";

var util = require('util');
var events = require('events');
var url = require('url');

var Internal = require('./internal');
var Define = require('./define');

var Route = module.exports = function() {
	var self = this;

	//Internal.on(Define.BARBARIAN_EVENT_INTERNAL_REQUEST, function(protocol) {
	Internal.on('request', function(protocol) {
		self.requestHandler(protocol);
	});
};

util.inherits(Route, events.EventEmitter);

Route.prototype.requestHandler = function(protocol) {
	var self = this;

	var req = url.parse(protocol.url);

	var res = {};
	res.send = function(data) {
		Internal.setContent(protocol.callback, data);
	};

	res.end = function(data) {
		Internal.setContent(protocol.callback, data);
		Internal.runCallback(protocol.callback);
	};

	self.emit('request', req, res);
};
