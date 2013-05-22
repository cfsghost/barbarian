"use strict";

var Barbarian = require('../../');

var barbarian = new Barbarian();

barbarian.init(function() {
	barbarian.createWindow('barbarian://content/');
	//barbarian.createWindow('barbarian://content/1aa/23.html');
	//barbarian.createWindow('barbarian://engine');
});

barbarian.on('request', function(req, res) {
	res.set('Content-Type', 'text/html');
	res.end('<h1>Nice Barbarian!</h1>');
});
