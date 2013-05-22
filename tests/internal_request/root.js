"use strict";

var Barbarian = require('../../');

var barbarian = new Barbarian();

barbarian.init(function() {
	barbarian.createWindow('barbarian://content/');
});

barbarian.on('request', function(req, res) {
	res.end('<h1>Nice Barbarian!</h1>');
});
