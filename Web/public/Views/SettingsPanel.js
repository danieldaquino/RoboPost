/*==============================

	SettingsPanel.js
	
	View for the Settings panel.
	
	Requirements:
	
	1. CarRobot.js
	2. main.css (Some classes are used)
	3. CloudRobot
	
	Crafted by Daniel Walnut

===============================*/
/*==============================

	Usage:
	
	1. Build the necessary HTML.
		a. A settings button.
		b. A panel div
		c. All required sliders, with labels next to them, inside the panel div
	
	2. Create new SettingsPanel object, passing all those HTML objects, as well as car object.

===============================*/


function SettingsPanel(InputCarRobot, InputCloudRobot, settingsButton, settingsPanelDiv, desiredSpeedSlider, cruiseKdSlider, cruiseKpSlider, motorKpSlider, motorKdSlider, sharpnessSlider, corneringPBrakeSlider, corneringDBrakeSlider, desiredSpeedDisplay, cruiseKpDisplay, cruiseKdDisplay, sharpnessDisplay, corneringPBrakeDisplay, corneringDBrakeDisplay, motorKpDisplay, motorKdDisplay) {
	var that = this;
	
	/*======
	Build the object children
	=======*/
	that.SettingsButton = settingsButton;
	that.SettingsPanelDiv = settingsPanelDiv;
	that.DesiredSpeedSlider = desiredSpeedSlider;
	that.CruiseKdSlider = cruiseKdSlider;
	that.CruiseKpSlider = cruiseKpSlider;
	that.MotorKpSlider = motorKpSlider;
	that.MotorKdSlider = motorKdSlider;
	that.SharpnessSlider = sharpnessSlider;
	that.CorneringPBrakeSlider = corneringPBrakeSlider;
	that.CorneringDBrakeSlider = corneringDBrakeSlider;
	that.DesiredSpeedDisplay = desiredSpeedDisplay;
	that.CruiseKpDisplay = cruiseKpDisplay;
	that.CruiseKdDisplay = cruiseKdDisplay;
	that.SharpnessDisplay = sharpnessDisplay;
	that.CorneringPBrakeDisplay = corneringPBrakeDisplay;
	that.CorneringDBrakeDisplay = corneringDBrakeDisplay;
	that.MotorKpDisplay = motorKpDisplay;
	that.MotorKdDisplay = motorKdDisplay;

	that.CarRobot = InputCarRobot;
	that.CloudRobot = InputCloudRobot;
	
	/*======
	Create methods
	=======*/
	that.ShowSettings = function() {
		that.SettingsPanelDiv.className = "TopBarButton Activated";
		that.SettingsButton.className = "TopBarButton Activated";
	}
	
	that.HideSettings = function() {
		that.SettingsPanelDiv.className = "TopBarButton";
		that.SettingsButton.className = "TopBarButton";
	}
	
	that.ShowHideSettings = function() {
		// Show/Hide Panel
		if(that.SettingsPanelDiv.className != "TopBarButton Activated") {
			that.ShowSettings();
		}
		else {
			that.HideSettings();
		}
	}

	that.UpdateSettings = function() {
		// Capture the values
		that.CarRobot.Settings.DesiredSpeed = that.DesiredSpeedSlider.value;
		that.CarRobot.Settings.Cruise.Kp = that.CruiseKpSlider.value;
		that.CarRobot.Settings.Cruise.Kd = that.CruiseKdSlider.value;
		that.CarRobot.Settings.Cruise.Sharpness = that.SharpnessSlider.value;
		that.CarRobot.Settings.Motor.Kp = that.MotorKpSlider.value;
		that.CarRobot.Settings.Motor.Kd = that.MotorKdSlider.value;
		that.CarRobot.Settings.Cruise.PBrake = that.CorneringPBrakeSlider.value;
		that.CarRobot.Settings.Cruise.DBrake = that.CorneringDBrakeSlider.value;
	
		// Update values on screen
		that.DesiredSpeedDisplay.innerText = that.CarRobot.Settings.DesiredSpeed;
		that.CruiseKpDisplay.innerText = that.CarRobot.Settings.Cruise.Kp;
		that.CruiseKdDisplay.innerText = that.CarRobot.Settings.Cruise.Kd;
		that.SharpnessDisplay.innerText = that.CarRobot.Settings.Cruise.Sharpness;
		that.CorneringPBrakeDisplay.innerText = that.CarRobot.Settings.Cruise.PBrake;
		that.CorneringDBrakeDisplay.innerText = that.CarRobot.Settings.Cruise.DBrake;
		that.MotorKpDisplay.innerText = that.CarRobot.Settings.Motor.Kp;
		that.MotorKdDisplay.innerText = that.CarRobot.Settings.Motor.Kd;
	}
	
	/*======
	Assign Events
	=======*/	
	var mouseOverOnce = false;
	that.SettingsPanelDiv.onmouseenter = function() {
		mouseOverOnce = true;
	}
	
	that.SettingsPanelDiv.onmouseleave = that.HideSettings;
	that.SettingsButton.onclick = that.ShowHideSettings;
	
	that.DesiredSpeed.oninput = that.UpdateSettings;
	that.CruiseKpSlider.oninput = that.UpdateSettings;
	that.CruiseKdSlider.oninput = that.UpdateSettings;
	that.SharpnessSlider.oninput = that.UpdateSettings;
	that.CorneringPBrakeSlider.oninput = that.UpdateSettings;
	that.CorneringDBrakeSlider.oninput = that.UpdateSettings;
	that.MotorKpSlider.oninput = that.UpdateSettings;
	that.MotorKdSlider.oninput = that.UpdateSettings;
	
	that.DesiredSpeed.onchange = that.CloudRobot.SendSettings;
	that.CruiseKpSlider.onchange = that.CloudRobot.SendSettings;
	that.CruiseKdSlider.onchange = that.CloudRobot.SendSettings;
	that.SharpnessSlider.onchange = that.CloudRobot.SendSettings;
	that.CorneringPBrakeSlider.onchange = that.CloudRobot.SendSettings;
	that.CorneringDBrakeSlider.onchange = that.CloudRobot.SendSettings;
	that.MotorKpSlider.onchange = that.CloudRobot.SendSettings;
	that.MotorKdSlider.onchange = that.CloudRobot.SendSettings;

}