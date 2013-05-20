"use strict";

var path = require('path');
var util = require('util');
var events = require('events');

var Define = require('./define');
var Internal = require('./internal');
var Route = require('./route');

var route = new Route();

var Barbarian = module.exports = function() {
	var self = this;

	self.instance = Internal;

	route.on('request', function(req) {
		self.emit('request', req);
	});
};

util.inherits(Barbarian, events.EventEmitter);

Barbarian.prototype.init = function(callback) {
	var self = this;

	var resPath = path.join(__dirname, '..', 'deps', 'cef', 'Resources');
	var subprocessPath = path.join(__dirname, '..', 'build', 'Release', 'subprocess.node');

	var localesPath = path.join(resPath, 'locales');
	self.instance.init(subprocessPath, resPath, localesPath);

	if (callback) {
		process.nextTick(function() {
			callback();
		});
	}
};

Barbarian.prototype.createWindow = function(url) {
	var self = this;

	self.instance.createWindow(url);
};
