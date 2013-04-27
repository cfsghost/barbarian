"use strict";

var path = require('path');
var _Barbarian = require('../build/Release/barbarian.node');

var Initialized = false;

var Barbarian = module.exports = function() {
};

Barbarian.prototype.init = function(callback) {
	var resPath = path.join(__dirname, '..', 'deps', 'cef', 'Resources');
	var localesPath = path.join(resPath, 'locales');
	_Barbarian.init(resPath, localesPath);

	if (callback)
		callback();
};

Barbarian.prototype.createWindow = function() {
	_Barbarian.createWindow();
};
