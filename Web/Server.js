const express = require('express');
const app = express();
var request = require('request');

app.get('/Hello', (req, res) => res.send('Hello World!'));

// Serve public html files
app.use(express.static('public'));

app.listen(3000, function() {
	console.log("=====================\n");
	console.log("Welcome to RoboPost!\n");
	console.log("=====================\n\n");
	console.log('Now live at localhost:3000\n');
});