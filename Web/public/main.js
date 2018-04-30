/*==============================

	Main.js
	
	RoboPost Web Interface
	
	Crafted by Daniel Walnut

===============================*/

/*======
Global Objects
=======*/

var PhotonKey = new Object();
var TheBotCanvas = new Object();
var UpdateMeasurementsInterval;
var TheRobotDataCSV;
var TheCloudRobot;
var TheCarRobot;
var TheSettingsPanel;
var TheStartStopButton;

/*====================

	~~Load~~
	
	Main load function, after webpage loads

=====================*/
function Load() {
	/*====
	Initialize Models 
	This should be the first in MVC
	=====*/
	TheCarRobot = new CarRobot();
	TheCarRobot.RetrieveSettings();
	
	/*====
	Initialize Controllers
	Must come before views!
	=====*/
	
	// Setup the CSV data collector.
	TheRobotDataCSV = new RobotDataCSV();
	TheRobotDataCSV.Init();
	
	// Setup Cloud Robot
	TheCloudRobot = new CloudRobot(TheCarRobot, TheRobotDataCSV);
	
	
	/*====
	Initialize Views 
	=====*/
		
	// Setup the Canvas.
	document.getElementById("BotCanvas").width = window.innerWidth;
	document.getElementById("BotCanvas").height = window.innerHeight - 100;
	// Initialize Canvas controller, then render.
	TheBotCanvas = new VisualBot(document.getElementById("BotCanvas"), TheCarRobot, function() {
		TheBotCanvas.Render();
	});
	
	// Setup the settings panel
	TheSettingsPanel = new SettingsPanel(
		TheCarRobot,
		TheCloudRobot,
		document.getElementById("ShowSettingsButton"),
		document.getElementById("SettingsPanelDiv"),
		document.getElementById("DesiredSpeed"),
		document.getElementById("CruiseKd"),
		document.getElementById("CruiseKp"),
		document.getElementById("CruiseKi"),
		document.getElementById("MotorKp"),
		document.getElementById("MotorKd"),
		document.getElementById("CruiseSharpness"),
		document.getElementById("CorneringPBrake"),
		document.getElementById("CorneringDBrake"),
		document.getElementById("DecayRate"),
		document.getElementById("DesiredSpeedDisplay"),
		document.getElementById("CruiseKpDisplay"),
		document.getElementById("CruiseKdDisplay"),
		document.getElementById("CruiseKiDisplay"),
		document.getElementById("CruiseSharpnessDisplay"),
		document.getElementById("CorneringPBrakeDisplay"),
		document.getElementById("CorneringDBrakeDisplay"),
		document.getElementById("DecayRateDisplay"),
		document.getElementById("MotorKpDisplay"),
		document.getElementById("MotorKdDisplay")
	);
	
	TheSettingsPanel.UpdateGUIToSettings();
	TheCloudRobot.SendSettings();
	
	// Setup the target view
	TheTargetView = new Target(TheCarRobot, TheCloudRobot);
	
	// Setup the Start Stop button
	TheStartStopButton = new StartStopButton(TheCarRobot, TheCloudRobot, document.getElementById("StartStopButtonElement"));
	
	TheMaestro = new Maestro(TheCarRobot, TheBotCanvas, TheStartStopButton, TheTargetView);
}
