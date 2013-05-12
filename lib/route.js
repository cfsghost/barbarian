"use strict";

var util = require('util');
var events = require('events');

var _Barbarian = require('../build/Release/barbarian.node');
var Define = require('./define');

var Route = module.exports = function() {
	var self = this;

	_Barbarian.on(Define.BARBARIAN_EVENT_INTERNAL_REQUEST, function(protocol) {
		self.emit('request', protocol);
	});

	self.on('request', function(protocol) {
		console.log(protocol);
	});
};

util.inherits(Route, events.EventEmitter);
