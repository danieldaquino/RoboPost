/*==============================

	Target.js
	
	View for the selection and handling of the robot targets.
	
	Requirements:
	1. CloudRobot.js
	
===============================*/

var DriftingRed = "rgb(236, 60, 30)";
var SettleBlue = "rgb(80, 211, 251)";

function Map(MapContainer, MapButton) {
	var that = this;
	that.MapContainer = MapContainer;
	that.MapContainer.className = "MapContainer";
	that.MapButton = MapButton;
	
	// Create Map Box
	that.Map = document.createElement("div");
	that.Map.className = "MapBox";
	that.MapContainer.appendChild(that.Map);
	
	//Create drop zones
	that.DropZones = new Array();
	
	that.DropZones[0] = document.createElement("div");
	that.DropZones[0].className = "DropZone";
	that.DropZones[0].style.top = "25.5%";
	that.DropZones[0].style.left = "27.5%";
	that.DropZones[0].style.width = "25.5%";
	that.DropZones[0].style.height = "12%";
	that.DropZones[0].style.borderColor = "#44F587";
	that.Map.appendChild(that.DropZones[0]);
	
	that.DropZones[1] = document.createElement("div");
	that.DropZones[1].className = "DropZone";
	that.DropZones[1].style.top = "61.5%";
	that.DropZones[1].style.left = "27.5%";
	that.DropZones[1].style.width = "20%";
	that.DropZones[1].style.height = "12%";
	that.DropZones[1].style.borderColor = "#44F587";
	that.Map.appendChild(that.DropZones[1]);
	
	that.DropZones[2] = document.createElement("div");
	that.DropZones[2].className = "DropZone";
	that.DropZones[2].style.top = "42%";
	that.DropZones[2].style.left = "49.8%";
	that.DropZones[2].style.width = "6%";
	that.DropZones[2].style.height = "26%";
	that.DropZones[2].style.borderColor = "#44F587";
	that.Map.appendChild(that.DropZones[2]);
	
	that.DropZones[3] = document.createElement("div");
	that.DropZones[3].className = "DropZone";
	that.DropZones[3].style.top = "42%";
	that.DropZones[3].style.left = "74%";
	that.DropZones[3].style.width = "6%";
	that.DropZones[3].style.height = "26%";
	that.DropZones[3].style.borderColor = "#44F587";
	that.Map.appendChild(that.DropZones[3]);
	
	//Create draggables
	that.RedStation = document.createElement("div");
	that.RedStation.className = "StationCircle";
	that.RedStation.style.background = DriftingRed;
	that.RedStation.draggable = true;
	that.RedStation.setAttribute('draggable', true);
	that.RedStation.addEventListener('dragstart', function(e) {
		e.dataTransfer.effectAllowed = 'move';
		e.dataTransfer.setData('Text', this.id);
		this.style.opacity = 0.4;
	}, false);
	that.Map.appendChild(that.RedStation);
	
	that.BlueStation = document.createElement("div");
	that.BlueStation.className = "StationCircle";
	that.BlueStation.style.background = SettleBlue;
	that.BlueStation.setAttribute('draggable', true);
	that.BlueStation.addEventListener('dragstart', function(e) {
		e.dataTransfer.effectAllowed = 'move';
		e.dataTransfer.setData('Text', this.id);
		this.style.opacity = 0.4;
	}, false);
	that.Map.appendChild(that.BlueStation);
	
	
	that.MapOpen = false;
	
	that.MapButton.onclick = function() {
		if(that.MapOpen) {
			// Close the map
			that.MapButton.className = "TopBarButton";
			that.MapContainer.className = "MapContainer";
			that.MapOpen = false;
		}
		else {
			// Open the map
			that.MapButton.className = "TopBarButton Activated";
			that.MapContainer.className = "MapContainer Visible";
			that.MapOpen = true;
		}
	}
	
	that.Resize = function() {
		if(that.MapContainer.clientWidth/that.MapContainer.clientHeight > 2) {
			//We are too wide! Glue on bottom and top
			that.Map.className = "MapBox GlueY";
		}
		else {
			// Glue on the sides
			that.Map.className = "MapBox GlueX";
		}
	}
}