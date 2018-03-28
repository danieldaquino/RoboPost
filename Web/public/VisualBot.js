/*==============================

	VisualBot.js
	
	Visual Robot Representation via Canvas
	
	Crafted by Daniel Walnut

===============================*/

function VisualBot(canvasObject, loadedCallback) {
	// Initialize Object
	var that = this;
	that.Canvas = canvasObject;
	var ctx = that.Canvas.getContext("2d");
	var RobotImage = new Image();
	RobotImage.src = "Outline.png";
	RobotImage.onload = function() {
		loadedCallback();
	}
	
	/*=======
	Robot State
	========*/
	that.Robot = new Object();
	that.Robot.SetPoints = new Object();
	that.Robot.SetPoints.CurveRadius = 32000;
	
	/*=======
	Visual Settings
	========*/	
	that.Visual = new Object();
	that.Visual.Size = 300;
	
	/*=======
	Exposed functions
	========*/
	that.Render = function() {
		RenderCurveRadius(300, "#000000", 20);
		RenderCar();
	}

	/*=======
	Internal functions
	========*/	
	var RenderCar = function() {
		ctx.drawImage(RobotImage, that.Canvas.width/2 - that.Visual.Size/2, that.Canvas.height/2 - that.Visual.Size/2, that.Visual.Size, that.Visual.Size);
	}
	
	var RenderCurveRadius = function(curveRadius, strokeStyle, lineWidth) {
		// Setup Pallette
		ctx.strokeStyle = strokeStyle;
		ctx.lineWidth = lineWidth;
		ctx.beginPath();
		ctx.arc(that.Canvas.width/2 + curveRadius, that.Canvas.height/2 + that.Visual.Size/4, curveRadius, Math.PI, 2*Math.PI, false);
		ctx.stroke();
	}
}