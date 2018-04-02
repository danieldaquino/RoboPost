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
		document.getElementById("ShowSettingsButton"),
		document.getElementById("SettingsPanelDiv"),
		document.getElementById("CruiseKd"),
		document.getElementById("CruiseKp"),
		document.getElementById("MotorKp"),
		document.getElementById("MotorKd"),
		document.getElementById("CruiseSharpness"),
		document.getElementById("CruiseKpDisplay"),
		document.getElementById("CruiseKdDisplay"),
		document.getElementById("CruiseSharpnessDisplay"),
		document.getElementById("MotorKpDisplay"),
		document.getElementById("MotorKdDisplay")
	);
	
	// Setup the Start Stop button
	TheStartStopButton = new StartStopButton(TheCarRobot, TheCloudRobot, document.getElementById("StartStopButtonElement"));
}
