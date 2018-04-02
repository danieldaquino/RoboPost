function RobotDataCSV() {
	var that = this;
	that.Text = "";
	
	that.Init = function() {
		that.Text = "Timestamp, Left RPM setpoint, Left RPM, Right RPM setpoint, Right RPM, Left PWM, Right PWM\n";
	}
	
	/*=======
	
	~~ Download ~~
	
	Downloads the current CSV file.
	
	========*/
	that.Download = function() {
		var blob = new Blob([that.Text], {type: "text/plain;charset=utf-8"});
		saveAs(blob, "RoboPostData.csv");		
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
