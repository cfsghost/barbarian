"use strict";

var util = require('util');
var events = require('events');

var Internal = require('./internal');
var Window = require('./window');

var WindowManager = module.exports = function(barbarian) {
	var self = this;

	self.barbarian = barbarian;
	self.windows = [];
};

util.inherits(Window, events.EventEmitter);

WindowManager.prototype.createWindow = function(url, callback) {
	var self = this;

	Internal.once('window_created', function(protocol) {
		window.instance = protocol.messageObject;
		self.windows.push(window);

		callback(window);
	});

	var window = new Window(url);
};
