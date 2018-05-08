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
	that.DropZones[0].addEventListener('dragover', function(e) {
		e.preventDefault();
		that.DropZones[0].className = "DropZone DragOver"
		e.dataTransfer.dropEffect = "move";
	});
	that.DropZones[0].addEventListener('dragleave', function() {
		that.DropZones[0].className = "DropZone Active"
	});
	that.DropZones[0].addEventListener('drop', function(e) {
		// DROP
		var TheID = e.dataTransfer.getData("TheID");
		that.DropZones[0].appendChild(document.getElementById(TheID));
	});
	that.Map.appendChild(that.DropZones[0]);
	
	that.DropZones[1] = document.createElement("div");
	that.DropZones[1].className = "DropZone";
	that.DropZones[1].style.top = "61.5%";
	that.DropZones[1].style.left = "27.5%";
	that.DropZones[1].style.width = "20%";
	that.DropZones[1].style.height = "12%";
	that.DropZones[1].addEventListener('dragover', function(e) {
		e.preventDefault();
		that.DropZones[1].className = "DropZone DragOver"
		e.dataTransfer.dropEffect = "move";
	});
	that.DropZones[1].addEventListener('dragleave', function() {
		that.DropZones[1].className = "DropZone Active"
	});
	that.DropZones[1].addEventListener('drop', function(e) {
		// DROP
		var TheID = e.dataTransfer.getData("TheID");
		that.DropZones[1].appendChild(document.getElementById(TheID));
	});
	that.Map.appendChild(that.DropZones[1]);
	
	that.DropZones[2] = document.createElement("div");
	that.DropZones[2].className = "DropZone";
	that.DropZones[2].style.top = "42%";
	that.DropZones[2].style.left = "49.8%";
	that.DropZones[2].style.width = "6%";
	that.DropZones[2].style.height = "26%";
	that.DropZones[2].addEventListener('dragover', function(e) {
		e.preventDefault();
		that.DropZones[2].className = "DropZone DragOver"
		e.dataTransfer.dropEffect = "move";
	});
	that.DropZones[2].addEventListener('dragleave', function() {
		that.DropZones[2].className = "DropZone Active"
	});
	that.DropZones[2].addEventListener('drop', function(e) {
		// DROP
		var TheID = e.dataTransfer.getData("TheID");
		that.DropZones[2].appendChild(document.getElementById(TheID));
	});
	that.Map.appendChild(that.DropZones[2]);
	
	that.DropZones[3] = document.createElement("div");
	that.DropZones[3].className = "DropZone";
	that.DropZones[3].style.top = "42%";
	that.DropZones[3].style.left = "74%";
	that.DropZones[3].style.width = "6%";
	that.DropZones[3].style.height = "26%";
	that.DropZones[3].addEventListener('dragover', function(e) {
		e.preventDefault();
		that.DropZones[3].className = "DropZone DragOver"
		e.dataTransfer.dropEffect = "move";
	});
	that.DropZones[3].addEventListener('dragleave', function() {
		that.DropZones[3].className = "DropZone Active"
	});
	that.DropZones[3].addEventListener('drop', function(e) {
		// DROP
		var TheID = e.dataTransfer.getData("TheID");
		that.DropZones[3].appendChild(document.getElementById(TheID));
	});

	that.Map.appendChild(that.DropZones[3]);
	
	//Create draggables
	that.RedStation = document.createElement("div");
	that.RedStation.className = "StationCircle";
	that.RedStation.id = "MapRedStation";
	that.RedStation.style.background = DriftingRed;
	that.RedStation.draggable = true;
	that.RedStation.setAttribute('draggable', true);
	that.RedStation.addEventListener('dragstart', function(e) {
		e.dataTransfer.effectAllowed = 'move';
		e.dataTransfer.setData('TheID', this.id);
		this.style.opacity = 0.4;
		that.ShowAllDropZones();
	}, false);
	that.RedStation.addEventListener('dragend', function(e) {
		this.style.opacity = 1;
		that.HideAllDropZones();
	}, false);
	that.Map.appendChild(that.RedStation);
	
	that.BlueStation = document.createElement("div");
	that.BlueStation.className = "StationCircle";
	that.BlueStation.id = "MapBlueStation";
	that.BlueStation.style.background = SettleBlue;
	that.BlueStation.setAttribute('draggable', true);
	that.BlueStation.addEventListener('dragstart', function(e) {
		e.dataTransfer.effectAllowed = 'move';
		e.dataTransfer.setData('TheID', this.id);
		this.style.opacity = 0.4;
		that.ShowAllDropZones();
	}, false);
	that.BlueStation.addEventListener('dragend', function(e) {
		this.style.opacity = 1;
		that.HideAllDropZones();
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
	
	that.ShowAllDropZones = function() {
		for(var i=0;i < that.DropZones.length;i++) {
			that.DropZones[i].className = "DropZone Active";
		}
	}
	
	that.HideAllDropZones = function() {
		for(var i=0;i < that.DropZones.length;i++) {
			that.DropZones[i].className = "DropZone";
		}
	}

}