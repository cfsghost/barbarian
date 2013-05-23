"use strict";

var util = require('util');
var events = require('events');

var Internal = require('./internal');

var Window = module.exports = function(url) {
	var self = this;

	self.instance = null;

	Internal.createWindow(url);
};

util.inherits(Window, events.EventEmitter);

Window.prototype.loadURL = function(url) {
	var self = this;

	Internal.windowInterface(self.instance, 'loadURL', url);
};
