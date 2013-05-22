"use strict";

var util = require('util');
var events = require('events');

var _Barbarian = require('../build/Release/barbarian.node');
var initialized = false;

var _Internal = null;

var Internal = module.exports = function() {
	var self = this;
};

util.inherits(Internal, events.EventEmitter);

var internalEvent = [
	'request'
];

if (!initialized) {
	// Initializing internal module
	initialized = true;

	// Clone native methods
	for (var method in _Barbarian) {
		Internal.prototype[method] = _Barbarian[method];
	}

	_Barbarian.setEventHandler(function(e) {

		_Internal.emit(internalEvent[e.event], e);
	});

	_Internal = module.exports = new Internal();
} else {
	module.exports = _Internal;
}

