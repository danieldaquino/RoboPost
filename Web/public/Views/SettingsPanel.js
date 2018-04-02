/*==============================

	SettingsPanel.js
	
	View for the Settings panel.
	
	Requirements:
	
	1. CarRobot.js
	2. main.css (Some classes are used)
	
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


function SettingsPanel(InputCarRobot, settingsButton, settingsPanelDiv, cruiseKdSlider, cruiseKpSlider, motorKpSlider, motorKdSlider, sharpnessSlider, cruiseKpDisplay, cruiseKdDisplay, sharpnessDisplay, motorKpDisplay, motorKdDisplay) {
	var that = this;
	
	/*======
	Build the object children
	=======*/
	that.SettingsButton = settingsButton;
	that.SettingsPanelDiv = settingsPanelDiv;
	that.CruiseKdSlider = cruiseKdSlider;
	that.CruiseKpSlider = cruiseKpSlider;
	that.MotorKpSlider = motorKpSlider;
	that.MotorKdSlider = motorKdSlider;
	that.SharpnessSlider = sharpnessSlider;
	that.CruiseKpDisplay = cruiseKpDisplay;
	that.CruiseKdDisplay = cruiseKdDisplay;
	that.SharpnessDisplay = sharpnessDisplay;
	that.MotorKpDisplay = motorKpDisplay;
	that.MotorKdDisplay = motorKdDisplay;

	that.CarRobot = InputCarRobot;
	
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
		that.CarRobot.Settings.Cruise.Kp = that.CruiseKpSlider.value;
		that.CarRobot.Settings.Cruise.Kd = that.CruiseKdSlider.value;
		that.CarRobot.Settings.Cruise.Sharpness = that.SharpnessSlider.value;
		that.CarRobot.Settings.Motor.Kp = that.MotorKpSlider.value;
		that.CarRobot.Settings.Motor.Kd = that.MotorKdSlider.value;
	
		// Update values on screen
		that.CruiseKpDisplay.innerText = that.CarRobot.Settings.Cruise.Kp;
		that.CruiseKdDisplay.innerText = that.CarRobot.Settings.Cruise.Kd;
		that.SharpnessDisplay.innerText = that.CarRobot.Settings.Cruise.Sharpness;
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
	that.CruiseKpSlider.oninput = that.UpdateSettings;
	that.CruiseKdSlider.oninput = that.UpdateSettings;
	that.SharpnessSlider.oninput = that.UpdateSettings;
	that.MotorKpSlider.oninput = that.UpdateSettings;
	that.MotorKdSlider.oninput = that.UpdateSettings;
}