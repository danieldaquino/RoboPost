/*==============================

	Main.js
	
	RoboPost Web Interface
	
	Crafted by Daniel Walnut

===============================*/


/*==========
Utility functions
===========*/

/*====================

	~~getRequest~~
	
	This function makes a get request to the given url.
	
	The function returns a promise, and the promise will resolve to the response text,
	or reject to the error.

=====================*/
function getRequest(url) {
	return xRequest(url, 'POST');
}

/*====================

	~~postRequest~~
	
	This function makes a get request to the given url.
	
	The function returns a promise, and the promise will resolve to the response text,
	or reject to the error.

=====================*/
function postRequest(url) {
	return xRequest(url, 'POST');
}

/*====================

	~~xRequest~~
	
	This function makes a request to the given url, using specified method
	
	The function returns a promise, and the promise will resolve to the response text,
	or reject to the error.

=====================*/
function xRequest(url, method) {
	return new Promise(function(resolve, reject) {
		// Check if browser supports AJAX requests
		if(window.XMLHttpRequest) {
			var xhr = new XMLHttpRequest();
		}
		else {
			reject('Browser not supported.');
		}
		
		// Open the request
		xhr.open(method, url);
	
		xhr.onreadystatechange = function() {
			if (xhr.readyState>3 && xhr.status==200) {
				resolve(xhr.responseText); // send the result back!
			}
			else {
				reject(xhr.responseText);
			}
		};
		xhr.setRequestHeader('X-Requested-With', 'XMLHttpRequest');
		xhr.send();
	});
}