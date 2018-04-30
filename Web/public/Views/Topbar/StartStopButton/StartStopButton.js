/*==============================

	StartStopButton.js
	
	Controls the view of the Start / Stop pushbutton
	
	Requirements:
	
	1. CarRobot.js model
	2. CloudRobot Controller.
			
	Crafted by Daniel Walnut

===============================*/

function StartStopButton(InputCarRobot, InputCloudRobot, buttonElement) {
	var that = this;
	
	that.Button = buttonElement;
	that.CarRobot = InputCarRobot;
	that.CloudRobot = InputCloudRobot;
	
	that.StartStop = function() {
		if(that.CarRobot.Settings.RobotPlay == false) {
			that.CarRobot.Settings.RobotPlay = true;
			that.Button.innerHTML = '<i class="fas fa-pause"></i>';
			that.Button.classList.add("Activated");
			that.CloudRobot.RobotPlay();
		}
		else {
			that.CarRobot.Settings.RobotPlay = false;		
			that.Button.innerHTML = '<i class="fas fa-play"></i>';
			that.Button.classList.remove("Activated");
			that.CloudRobot.RobotPause();
		}		
	}
	
	that.Button.onclick = that.StartStop;
}