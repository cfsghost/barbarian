"use strict";

var Barbarian = require('../../');

var barbarian = new Barbarian();

barbarian.init(function() {
	barbarian.createWindow('barbarian://content/');
});

barbarian.on('request', function(req, callback) {
	callback();
	console.log(req);
	console.log(callback);
});
