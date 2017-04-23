function gatherData() {	
	var v = document.forms["algoData"]["season"].value
	var w = document.forms["algoData"]["outlook"].value
	var x = document.forms["algoData"]["temp"].value;
	var y = document.forms["algoData"]["wind"].value;
	var z = document.forms["algoData"]["humidity"].value;
	var div = document.getElementById("result");
	var result = document.getElementById("theResult");
	
	if (x == "Enter Temperature") {
		x = "undefined";
	}
	if (y == "Enter Wind Speed") {
		y = "undefined";
	}
	if (z == "Enter Humidity Percentage") {
		z = "undefined";
	}
	
	var data = v + ", " + w + ", " + x + ", " + y + ", " + z;
	var stock = compute(w, x, y, v, z);
	
	div.innerHTML += '<fieldset class="textarea"><h1 class="arial">Based off the data: ' + data + '<br>The market is predicted to go ' + stock + '</h1></fieldset>';
	//div.innerHTML += '<fieldset class="textarea"><h1 class="arial">The market is predicted to go ' + stock + '</h1></fieldset>';

}