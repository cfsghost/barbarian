"use strict";

var Barbarian = require('../../');

var barbarian = new Barbarian();

barbarian.init(function() {
	barbarian.createWindow('barbarian://engine');
});

barbarian.on('request', function(req, res) {
	console.log(req);
	res.set('Content-Type', 'text/html');
	res.end('<h1>Nice Barbarian!</h1>');
});
