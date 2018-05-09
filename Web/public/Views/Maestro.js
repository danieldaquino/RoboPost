/*==============================

	Maestro.js
	
	Controls the flow of UI
	
	Requirements:
	
	Models
	1. Stations
	2. CarRobot
	3. CloudRobot
	
	Views
	2. StartStopButton
	3. VisualBot
	4. Target View
	
	Crafted by Daniel Walnut

===============================*/

function Maestro(CarRobot, VisualBot, StartStopButton, Target, CloudRobot, Stations) {
	var that = this;
	
	that.State = "Choose";
	that.CarRobot = CarRobot;
	that.VisualBot = VisualBot;
	that.StartStopButton = StartStopButton;
	that.Target = Target;
	that.CloudRobot = CloudRobot;
	that.Stations = Stations;
	that.ColorTarget = 0;
	
	// STATE LOGIC
	
	that.GoToChooseState = function() {
		that.VisualBot.Canvas.style.opacity = 0;
		that.Target.GoToMiddle();
	}
	
	that.GoToRunningState = function() {
		that.VisualBot.RenderState = "Running";
		that.VisualBot.Render();
		setTimeout(function() {
			that.VisualBot.Canvas.style.opacity = 1;
			that.Target.GoToCorner();
		}, 500);
	}
	
	that.GoToGoToNextState = function() {
		that.VisualBot.RenderState = "Running";
		that.VisualBot.Render();
		setTimeout(function() {
			that.VisualBot.Canvas.style.opacity = 1;
			that.Target.GoToCorner();
		}, 500);
	}
	
	that.GoToState = function(state) {
		switch(state) {
			case "Choose":
				that.GoToChooseState();
				break;
			case "Running":
				that.GoToRunningState();				
				break;
			case "GoToNext":
				that.GoToGoToNextState();				
				break;
			default:
				return false;
				break;
		}
		that.State = state;
		return true;
	}
	
	// STATE TRANSITIONS
		
	// Append event listener to the Selecting target event
	that.OriginalSelectTarget = that.Target.SelectTarget;
	that.Target.SelectTarget = function(CommandColor) {
		if(that.CarRobot.Targets.CommandColor == CommandColor && CommandColor != 0) {
			// We are already going there. Go to state "Go To next"
			// Select the CommandColor on the UI
			that.OriginalSelectTarget(CommandColor);
			// Set the actual command color to zero to let it run.
			that.CarRobot.Targets.CommandColor = 0;
			that.CarRobot.Targets.PathChosen = that.Stations.PathChosen[CommandColor];
			that.CloudRobot.SendSettings();
			that.ColorTarget = CommandColor;
			// Go to "Go to next" state
			that.GoToState("GoToNext");
			return;
		}
		else {
			// Select it on UI
			that.OriginalSelectTarget(CommandColor);
			// Go to command color
			that.CarRobot.Targets.CommandColor = CommandColor;
			that.CarRobot.Targets.PathChosen = that.Stations.PathChosen[CommandColor];
			that.CloudRobot.SendSettings();
			that.ColorTarget = CommandColor;
			// Start Running
			that.GoToState("Running");
		}
	}
	
	var TheColor = CarRobot.Measurements.Color;
	// Append event listener to the color measurement
	Object.defineProperty(that.CarRobot.Measurements, "Color", {
		get() {
			return TheColor;
		},
		set(newValue) {
			TheColor = newValue;
			if(that.State == "Running" && TheColor == that.CarRobot.Targets.CommandColor && that.CarRobot.Targets.CommandColor != 0) {
				that.Target.ShowSelect();
				that.VisualBot.RenderState = "Completion";
				that.VisualBot.StationColor = that.CarRobot.Targets.CommandColor;
				that.VisualBot.Render();
			}
			else if(that.State == "GoToNext") {
				if(TheColor == 0) {
					// It saw white on the "GoToNext" state, which means we left the station. Debounce.
					setTimeout(function() {
						// Check if this is still white.
						if(TheColor == 0) {
							// Yes!! ready to set actual target.
							that.CarRobot.Targets.CommandColor = that.ColorTarget;
							that.CloudRobot.SendSettings();
							that.GoToState("Running");
						}
					}, 1500);
				}
			}
		}
	});
	
	//GO TO FIRST STATE
	
	// Start	
	that.GoToState(that.State);
}