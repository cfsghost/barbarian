"use strict";

var path = require('path');
var util = require('util');
var events = require('events');

var Define = require('./define');
var Internal = require('./internal');
var Route = require('./route');
var WindowManager = require('./window_manager');
var ContentManager = require('./content_manager');

var route = new Route();

var Barbarian = module.exports = function() {
	var self = this;

	self.instance = Internal;

	// Initializing window manager
	self.windowManager = new WindowManager(self);

	// Initializing content manager
	self.content = new ContentManager(self);
	self.content.mainPath = path.dirname(require.main.filename);

	route.on('request', function(req, res) {
		var args = [ 'request' ];

		switch(req.host) {
		case 'content':

			// Using internal implementation to load content resource
			self.content.loadResource(req, res);
			break;

		default:

			// Fire event
			self.emit.apply(self, args.concat(Array.prototype.splice.call(arguments, 0)));

		}
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

Barbarian.prototype.createWindow = function(url, callback) {
	var self = this;

	self.windowManager.createWindow(url, function(window) {
		callback(window);
	});

	return self;
};

Barbarian.prototype.registerExtension = function(name, code) {
	var self = this;

	Internal.registerExtension(name, code);
};
