/*==============================

	Maestro.js
	
	Controls the flow of UI
	
	Requirements:
	
	Views
	2. StartStopButton
	3. VisualBot
	4. Target View
	
	Crafted by Daniel Walnut

===============================*/

function Maestro(CarRobot, VisualBot, StartStopButton, Target) {
	var that = this;
	
	that.State = "Choose";
	that.CarRobot = CarRobot;
	that.VisualBot = VisualBot;
	that.StartStopButton = StartStopButton;
	that.Target = Target;
	
	// STATE LOGIC
	
	that.GoToChooseState = function() {
		that.VisualBot.Canvas.style.opacity = 0;
		that.Target.GoToMiddle();
	}
	
	that.GoToRunningState = function() {
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
		if(that.CarRobot.Targets.CommandColor == CommandColor) {
			// We are already going there. Ignore this event.
			return;
		}
		that.OriginalSelectTarget(CommandColor);
		that.GoToState("Running");
		that.VisualBot.RenderState = "Running";
		that.VisualBot.Render();
	}
	
	var TheColor = CarRobot.Measurements.Color;
	// Append event listener to the color measurement
	Object.defineProperty(that.CarRobot.Measurements, "Color", {
		get() {
			return TheColor;
		},
		set(newValue) {
			TheColor = newValue;
			if(TheColor == that.CarRobot.Targets.CommandColor && that.CarRobot.Targets.CommandColor != 0) {
				that.Target.ShowSelect();
				that.VisualBot.RenderState = "Completion";
				that.VisualBot.StationColor = that.CarRobot.Targets.CommandColor;
				that.VisualBot.Render();
			}			
		}
	});
	
	//GO TO FIRST STATE
	
	// Start	
	that.GoToState(that.State);
}