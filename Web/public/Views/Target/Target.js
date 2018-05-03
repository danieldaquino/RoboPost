/*==============================

	Target.js
	
	View for the selection and handling of the robot targets.
	
	Requirements:
	1. CarRobot.js
	
===============================*/
var DriftingRed = "rgb(236, 60, 30)";
var SettleBlue = "rgb(80, 211, 251)";

function Target(CarRobot, CloudRobot) {
	var that = this;
	
	that.CarRobot = CarRobot;
	that.CloudRobot = CloudRobot;
	
	that.HTML = new Object();
	that.HTML.Main = document.createElement("div");
	that.HTML.Main.className = "TargetMainDiv Middle";
	
	that.HTML.Label = document.createElement("h3");
	that.HTML.Label.innerText = "Select Target";
	that.HTML.Main.appendChild(that.HTML.Label);
	
	//RED
	that.HTML.RedTarget = document.createElement("div");
	that.HTML.RedTarget.className = "TargetCircle";
	that.HTML.RedTarget.style.background = DriftingRed;
	that.HTML.RedTarget.style.color = DriftingRed;
	that.HTML.Main.appendChild(that.HTML.RedTarget);

	//BLUE
	that.HTML.BlueTarget = document.createElement("div");
	that.HTML.BlueTarget.className = "TargetCircle";
	that.HTML.BlueTarget.style.background = SettleBlue;
	that.HTML.BlueTarget.style.color = SettleBlue;
	that.HTML.Main.appendChild(that.HTML.BlueTarget);
	
	//NO TARGET
	that.HTML.NoTarget = document.createElement("div");
	that.HTML.NoTarget.className = "TargetCircle";
	that.HTML.NoTarget.style.border = "solid #000000 3px";
	that.HTML.NoTarget.style.background = "#FFFFFF";
	that.HTML.NoTarget.style.color = "#000000";
	that.HTML.Main.appendChild(that.HTML.NoTarget);

	
	that.SelectTarget = function(CommandColor) {
		that.CarRobot.Targets.CommandColor = CommandColor;
		setTimeout(function() {
			if(CommandColor == 0) {
				// Start animation
				that.HTML.NoTarget.className = "TargetCircle PulsatingBlack";
				that.HTML.BlueTarget.className = "TargetCircle";
				that.HTML.RedTarget.className = "TargetCircle";
				that.HTML.Label.innerText = "Free Run";
			}
			else if(CommandColor == 1) {
				// Start animation
				that.HTML.RedTarget.className = "TargetCircle PulsatingRed";
				that.HTML.BlueTarget.className = "TargetCircle";
				that.HTML.NoTarget.className = "TargetCircle";
				that.HTML.Label.innerText = "Going to: Red Station";
			}
			else if(CommandColor == 2) {
				that.HTML.BlueTarget.className = "TargetCircle PulsatingBlue";			
				that.HTML.RedTarget.className = "TargetCircle";
				that.HTML.NoTarget.className = "TargetCircle";
				that.HTML.Label.innerText = "Going to: Blue Station";
			}
			else {
				return false;
			}
			// SEND THE SETTINGS
			that.CloudRobot.SendSettings();
		}, 500);
	}
	
	that.ShowSelect = function() {
		that.HTML.RedTarget.className = "TargetCircle";
		that.HTML.BlueTarget.className = "TargetCircle";
		that.HTML.NoTarget.className = "TargetCircle";
		that.HTML.Label.innerText = "Select Target";		
	}
	
	//Movement State Functions
	that.GoToMiddle = function() {
		that.HTML.Main.className = "TargetMainDiv Middle";
	}
	
	that.GoToCorner = function() {
		that.HTML.Main.className = "TargetMainDiv Corner";
	}
	
	that.HTML.RedTarget.onmouseup = function() {
		// Select Red
		that.SelectTarget(1);
	}
	
	that.HTML.BlueTarget.onmouseup = function() {
		// Select Blue
		that.SelectTarget(2);		
	}
	
	that.HTML.NoTarget.onmouseup = function() {
		// Select No Target
		that.SelectTarget(0);		
	}

		
	document.body.appendChild(that.HTML.Main);
}