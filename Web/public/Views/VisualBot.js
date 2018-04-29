/*==============================

	VisualBot.js
	
	Visual Robot Representation via HTML5 Canvas
	
	Requirements:
	1. CarRobot.js
	
	Crafted by Daniel Walnut

===============================*/

/*=======
Global Colours
========*/
var DriftingRed = "rgb(236, 60, 30)";
var SettleBlue = "rgb(80, 211, 251)";
var TapeBlack = "#000000";

function VisualBot(canvasObject, InputCarRobot, loadedCallback) {
	// Initialize Object
	var that = this;
	that.Canvas = canvasObject;
	that.Robot = InputCarRobot;
	var ctx = that.Canvas.getContext("2d");
	var RobotImage = new Image();
	RobotImage.src = "/Graphics/Outline.png";
	RobotImage.onload = function() {
		loadedCallback();
	}
	
		
	/*=======
	Visual Settings
	========*/	
	that.Visual = new Object();
	that.Visual.Size = 500;
	that.Visual.Margin = -50;
	
	/*=======
	Exposed functions
	========*/
	that.Render = function() {
		// Clear canvas for redrawing.
		ctx.clearRect(0, 0, that.Canvas.width, that.Canvas.height);
		RenderCurveRadius(that.Robot.Measurements.CurveRadius, DriftingRed, 10);
		RenderCurveRadius(that.Robot.SetPoints.CurveRadius, SettleBlue, 10);
		RenderCar();
		RenderMotorBox(0);
		RenderMotorBox(1);
		RenderSpeedBox();
	}

	/*=======
	Internal functions
	========*/
	document.body.onresize = function() {
		that.Canvas.width = window.innerWidth;
		that.Canvas.height = window.innerHeight - 100;
		that.Render();
	}
		
	var RenderCar = function() {
		ctx.drawImage(RobotImage, that.Canvas.width/2 - that.Visual.Size/2, that.Canvas.height - that.Visual.Size - that.Visual.Margin, that.Visual.Size, that.Visual.Size);
	}
	
	var RenderCurveRadius = function(curveRadius, strokeStyle, lineWidth) {
		// Setup Pallette
		ctx.strokeStyle = strokeStyle;
		ctx.lineWidth = lineWidth;
		// Begin the path.
		ctx.beginPath();
		// Calculate curve radius in px.
		var pxCurveRadius;
		if(curveRadius == Infinity) {
			curveRadius = 32767;
		}
		pxCurveRadius = curveRadius/(that.Robot.Parameters.WheelBase/(that.Visual.Size*0.5));
		if(curveRadius > 0) {
			// Positive curve radius
			ctx.arc(that.Canvas.width/2 + pxCurveRadius, that.Canvas.height/2 + that.Visual.Size/4, pxCurveRadius, Math.PI, 1.75*Math.PI, false);
		}
		else {
			// Negative Curve Radius
			pxCurveRadius = -pxCurveRadius;
			ctx.arc(that.Canvas.width/2 - pxCurveRadius, that.Canvas.height/2 + that.Visual.Size/4, pxCurveRadius, 2*Math.PI, 1.25*Math.PI, true);
		}
		ctx.stroke();
	}
	
	var RenderSpeedBox = function() {
		// General dimensions
		var boxWidth = 100;
		var bottomMargin = 30;
		var boxHeight = 100;
		var headingYMargin = 28;
		var headingSize = 28;
		var cellPadding = 10;
		// Setup Origins
		var xBegin = that.Canvas.width/2 - boxWidth/2;
		var yBegin = that.Canvas.height - bottomMargin - boxHeight;
		// Setup Y Cursor
		var yCursor = yBegin;
		// Draw top border
		// Setup colors and borders
		ctx.strokeStyle = TapeBlack;
		ctx.lineWidth = 4;
		ctx.beginPath();
		ctx.moveTo(xBegin, yCursor);
		ctx.lineTo(xBegin + boxWidth, yCursor);
		ctx.stroke();
		// Draw Block Heading
		yCursor += headingYMargin;	// Move Cursor
		ctx.font= headingSize + "px Futura";
		ctx.fillText((that.Robot.Measurements.Speed/100).toFixed(2) + " m/s", xBegin, yCursor);
		// Draw bottom border
		yCursor += cellPadding;
		ctx.strokeStyle = TapeBlack;
		ctx.lineWidth = 4;
		ctx.beginPath();
		ctx.moveTo(xBegin, yCursor);
		ctx.lineTo(xBegin + boxWidth, yCursor);
		ctx.stroke();
	}
	
	var RenderMotorBox = function(motor) {
		// General dimensions
		var boxWidth = 200;
		var boxMargin = 120;
		var textYMargin = 18;
		var textSize = 14;
		var cellPadding = 15;
		var headingYMargin = 36;
		var headingSize = 36;
		var PWMDiagramHeight = 50;
		var barHeight = 30;
		// Calculate the top and left origin
		if(motor == 0) {
			var xBegin = that.Canvas.width/2 - that.Visual.Size/2 - boxMargin;
		}
		else {
			var xBegin = that.Canvas.width/2 + that.Visual.Size/2 + boxMargin - boxWidth;
		}
		var yBegin = that.Canvas.height/2 - 100;
		// Setup Y Cursor
		var yCursor = yBegin;
		// Draw top border
		// Setup colors and borders
		ctx.strokeStyle = TapeBlack;
		ctx.lineWidth = 6;
		ctx.beginPath();
		ctx.moveTo(xBegin, yCursor);
		ctx.lineTo(xBegin + boxWidth, yCursor);
		ctx.stroke();
		// Draw Block Heading
		yCursor += headingYMargin;	// Move Cursor
		ctx.font= headingSize + "px Futura";
		if(motor == 0) {
			ctx.fillText("Left Motor", xBegin, yCursor);
		}
		else {
			ctx.fillText("Right Motor", xBegin, yCursor);		
		}
		// Draw Separator
		yCursor += cellPadding;
		ctx.strokeStyle = TapeBlack;
		ctx.lineWidth = 2;
		ctx.beginPath();
		ctx.moveTo(xBegin, yCursor);
		ctx.lineTo(xBegin + boxWidth, yCursor);
		ctx.stroke();
		// Draw PWM diagram
		yCursor += cellPadding;	// Move Cursor
		ctx.strokeStyle = DriftingRed;
		ctx.lineWidth = 4;
		ctx.beginPath();
		ctx.moveTo(xBegin, yCursor + PWMDiagramHeight);
		ctx.lineTo(xBegin, yCursor);
		ctx.lineTo(xBegin + boxWidth*that.Robot.Measurements.PWM[motor].toFixed(2), yCursor);
		ctx.lineTo(xBegin + boxWidth*that.Robot.Measurements.PWM[motor].toFixed(2), yCursor + PWMDiagramHeight);
		ctx.lineTo(xBegin + boxWidth, yCursor + PWMDiagramHeight);
		ctx.stroke();
		yCursor += PWMDiagramHeight;	// Move Cursor
		// Draw PWM Number
		yCursor += textYMargin + cellPadding;	// Move Cursor
		ctx.font= textSize + "px Futura";
		ctx.fillText((that.Robot.Measurements.PWM[motor]*100).toFixed(0) + "% – " + that.Robot.Measurements.F[motor].toFixed(0) + "Hz", xBegin, yCursor);
		// Draw Measured Speed bar
		yCursor += cellPadding;
		ctx.fillStyle = DriftingRed;
		ctx.fillRect(xBegin, yCursor, boxWidth*(that.Robot.Measurements.RPM[motor]/that.Robot.Parameters.MaxRPM), barHeight);
		ctx.fillStyle = TapeBlack;
		yCursor += barHeight;
		// Draw Measured Speed Number
		yCursor += textYMargin + cellPadding;	// Move Cursor
		ctx.font= textSize + "px Futura";
		ctx.fillText((that.Robot.Measurements.RPM[motor]) + " RPM", xBegin, yCursor);
		// Draw Setpoint Speed bar
		yCursor += cellPadding;
		ctx.fillStyle = SettleBlue;
		ctx.fillRect(xBegin, yCursor, boxWidth*(that.Robot.SetPoints.RPM[motor]/that.Robot.Parameters.MaxRPM), barHeight);
		ctx.fillStyle = TapeBlack;
		yCursor += barHeight;
		// Draw Setpoint Speed Number
		yCursor += textYMargin + cellPadding;	// Move Cursor
		ctx.font= textSize + "px Futura";
		ctx.fillText((that.Robot.SetPoints.RPM[motor]) + " RPM", xBegin, yCursor);
		// Draw bottom border
		yCursor += cellPadding;
		ctx.strokeStyle = TapeBlack;
		ctx.lineWidth = 6;
		ctx.beginPath();
		ctx.moveTo(xBegin, yCursor);
		ctx.lineTo(xBegin + boxWidth, yCursor);
		ctx.stroke();
	}
}