"use strict";

var path = require('path');
var fs = require('fs');

var ContentManager = module.exports = function(barbarian) {
	var self = this;

	self.barbarian = barbarian;
	self.mainPath = '.';
};

ContentManager.prototype.loadResource = function(req, res) {
	var self = this;

	function loadFile(filepath) {
		// Read file
		fs.readFile(filepath, function(err, data) {
			res.end(data);
		});
	}

	function checkDefault(filepath) {
		filepath = path.join(filepath, 'index.html');

		fs.exists(filepath, function(exists) {
			if (!exists) {
				notFound();
				return;
			}

			loadFile(filepath);
		});
	}

	function notFound() {
		res.status(404);
		res.end('<h1>404 Not found</h1>');
	}

	var filepath = path.join(self.mainPath, req.path);
	fs.exists(filepath, function(exists) {

		if (!exists) {
			notFound();
			return;
		}

		// default document
		fs.lstat(filepath, function(err, stats) {
			if (stats.isDirectory()) {
				// Using index.html by default
				checkDefault(filepath);
				return;
			}

			loadFile(filepath);
		});
	});
};
