RobotSettings = new Object();

RobotSettings.Motor = new Object();
RobotSettings.Motor.Kp = 0;
RobotSettings.Motor.Kd = 0;
RobotSettings.Cruise = new Object();
RobotSettings.Cruise.Kp = 0;
RobotSettings.Cruise.Kd = 0;

function HideSettings() {
	var SettingsPanelElement = document.getElementById("SettingsPanel");
	SettingsPanelElement.className = "TopBarButton";
	document.getElementById("ShowSettingsButton").className = "TopBarButton";
}

function ShowSettings() {
	var SettingsPanelElement = document.getElementById("SettingsPanel");
	SettingsPanelElement.className = "TopBarButton Activated";
	document.getElementById("ShowSettingsButton").className = "TopBarButton Activated";
}

function ShowHideSettings() {
	var SettingsPanelElement = document.getElementById("SettingsPanel");
	if(document.getElementById("SettingsPanel").className != "TopBarButton Activated") {
		ShowSettings();
	}
	else {
		HideSettings();
	}
}

function InitializeSettingsPanel() {
	var mouseOverOnce = false;
	var SettingsPanelElement = document.getElementById("SettingsPanel");
	SettingsPanelElement.onmouseenter = function() {
		mouseOverOnce = true;
	}
	SettingsPanelElement.onmouseleave = function() {
		HideSettings();
	}
}

function UpdateSettings() {
	// Capture the values
	RobotSettings.Motor.Kp = document.getElementById("MotorKp").value;
	RobotSettings.Motor.Kd = document.getElementById("MotorKd").value;
	RobotSettings.Cruise.Kp = document.getElementById("CruiseKp").value;
	RobotSettings.Cruise.Kd = document.getElementById("CruiseKd").value;
	
	// Update values on screen
	document.getElementById("MotorKpDisplay").innerText = RobotSettings.Motor.Kp;
	document.getElementById("MotorKdDisplay").innerText = RobotSettings.Motor.Kd;
	document.getElementById("CruiseKpDisplay").innerText = RobotSettings.Cruise.Kp;
	document.getElementById("CruiseKdDisplay").innerText = RobotSettings.Cruise.Kd;
}