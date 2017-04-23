$(function() {
	$('input[type=radio]').checkboxradio();
	$('input').on('change', function() {
		var v = $('input[name=season]:checked + label').text().trim().toLowerCase();
		var w = $('input[name=outlook]:checked + label').text().trim().toLowerCase();
		var x = $('input[name=temp]').val();
		var y = $('input[name=wind]').val();
		var z = $('input[name=humidity]').val();
		
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
		console.log(data);
		var probs = compute(w, x, y, v, z);
		$('#up_prob').text(probs.up);
		$('#down_prob').text(probs.down);
	});
});