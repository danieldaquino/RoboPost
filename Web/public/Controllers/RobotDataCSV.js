function RobotDataCSV() {
	var that = this;
	that.Text = "";
	
	that.Init = function() {
		that.Text = "Timestamp, last Sensor Position, Linear Speed Setpoint, Linear Speed measurement, Curve Radius Setpoint, Curve Radius Measured, Left RPM setpoint, Left RPM, Right RPM setpoint, Right RPM, Left PWM Frequency, Left PWM Duty Cycle, Right PWM Frequency, Right PWM Duty Cycle, , DesiredSpeed, SharpestCurve, Cruise Kp, Cruise Kd, Cruise Ki, DBrake, PBrake, Decay Rate, Motor Kp, Motor Kd\n";
	}
	
	/*=======
	
	~~ Download ~~
	
	Downloads the current CSV file.
	
	========*/
	that.Download = function() {
		var blob = new Blob([that.Text], {type: "text/plain;charset=utf-8"});
		saveAs(blob, "RoboPostData.csv");
		that.Init();
	}
	
	/*=======
	
	~~ WriteRow ~~
	
	Writes a Row to the CSV.
	
	inputs:
		valuesArray: an array of values to be written to the row. Each will be written to its cell.
	
	========*/
	that.WriteRow = function(valuesArray) {
		var CSVBuffer = "";
		// Add first element
		if(valuesArray.length > 0) {
			CSVBuffer += valuesArray[0];
		}
		// Add all other elements, comma separated
		for(var i=1; i < valuesArray.length;i++) {
			CSVBuffer += ", " + valuesArray[i];
		}
		// Add line break
		CSVBuffer += "\n";
		// Append to our file...
		that.Text += CSVBuffer;
	}
}
