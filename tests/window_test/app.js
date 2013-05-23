"use strict";

var Barbarian = require('../../');

var barbarian = new Barbarian();

barbarian.init(function() {
	barbarian.createWindow('http://www.mandice.com/', function() {
		console.log('First window was created');
	});
	barbarian.createWindow('http://stem.mandice.org/', function() {
		console.log('Second window was created');
	});
});
