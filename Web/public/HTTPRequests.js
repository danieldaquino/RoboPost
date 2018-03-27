/*==============================

	HTTPRequests.js
	
	Utility functions for AJAX HTTP requests with promises.
	
	Crafted by Daniel Walnut

===============================*/

/*==========
Utility functions
===========*/

/*====================

	~~GetRequest~~
	
	This function makes a get request to the given url.
	
	The function returns a promise, and the promise will resolve to the response text,
	or reject to the error.

=====================*/
function GetRequest(url) {
	return XRequest(url, 'GET');
}

/*====================

	~~postRequest~~
	
	This function makes a get request to the given url.
	
	The function returns a promise, and the promise will resolve to the response text,
	or reject to the error.

=====================*/
function PostRequest(url) {
	return XRequest(url, 'POST');
}

/*====================

	~~XRequest~~
	
	This function makes a request to the given url, using specified method
	
	The function returns a promise, and the promise will resolve to the response text,
	or reject to the error.

=====================*/
function XRequest(url, method) {
	return new Promise(function(resolve, reject) {
		// Setup request
		var req = new XMLHttpRequest();
		req.open(method, url);
		req.setRequestHeader('X-Requested-With', 'XMLHttpRequest');
	    req.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
		
		// When request is ready
		req.onload = function() {
			if(req.status == 200) {
				resolve(req.response);
			}
			else {
				reject(Error(req.statusText));
			}
		}
		// When request fails
		req.onerror = function() {
			reject(Error("Network Error"));
		}		
		
		// Actually send request
		req.send();
	});
}

/*====================

	~~GetJSON~~
	
	This function makes a get request to the given url, and gathers the json
	
	The function returns a promise, and the promise will resolve to the response json,
	or reject to the error.

=====================*/
function GetJSON(url) {
	return new Promise(function(resolve, reject) {
		// First, get with getRequest
		GetRequest(url).then(function(response) {
			// Parse JSON and return that
			resolve(JSON.parse(response));
		}).catch(function(error) {
			// Something went wrong man.
			reject(error);
		});
	});
}