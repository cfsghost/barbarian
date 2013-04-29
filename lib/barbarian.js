"use strict";

var path = require('path');
var _Barbarian = require('../build/Release/barbarian.node');

var Initialized = false;

var Barbarian = module.exports = function() {
};

Barbarian.prototype.init = function(callback) {
	var resPath = path.join(__dirname, '..', 'deps', 'cef', 'Resources');
	var subprocessPath = path.join(__dirname, '..', 'build', 'Release', 'subprocess.node');
	console.log(subprocessPath);
	var localesPath = path.join(resPath, 'locales');
	_Barbarian.init(subprocessPath, resPath, localesPath);

	if (callback)
		callback();
};

Barbarian.prototype.createWindow = function() {
	_Barbarian.createWindow();
};
