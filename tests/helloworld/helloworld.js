"use strict";

var Barbarian = require('../../');

var barbarian = new Barbarian();

barbarian.init(function() {
	barbarian.createWindow('http://www.mandice.com/');
});
