
function makeHslString(disp) {
	return "hsl(" + disp.hue + ", " + disp.saturation + "%, " + disp.lightness + "%)";
}

function updateDisplay() {
	this.hue = Math.max(0, Math.min(this.hue, 360));
	this.saturation = Math.max(0, Math.min(this.saturation, 100));
	this.lightness = Math.max(0, Math.min(this.lightness, 100));
	document.getElementById(this.id + "-hue").value = this.hue;
	document.getElementById(this.id + "-saturation").value = this.saturation;
	document.getElementById(this.id + "-lightness").value = this.lightness;
	document.getElementById(this.id + "-color").setAttribute("style", "background-color:" + makeHslString(this));
}

function createColorDisplay(id) {
	
	var h = document.getElementById(id + "-hue");
	var s = document.getElementById(id + "-saturation");
	var l = document.getElementById(id + "-lightness");
	if (!h || !s || !l) return;

	var disp = {
		id: id,
		hue: parseInt(h.value),
		saturation: parseInt(s.value),
		lightness: parseInt(l.value),
		update: updateDisplay
	}
	var container = document.getElementById(id + "-color-container");
	if (!container) return;

	var color = document.createElement("div");
	color.setAttribute("id", id + "-color");
	color.setAttribute("class", "colordisplay");
	container.appendChild(color);
	
	h.addEventListener("change", function (evt) {
		disp.hue = evt.srcElement.value;
		disp.update();
	});

	s.addEventListener("change", function (evt) {
		disp.saturation = evt.srcElement.value;
		disp.update();
	});
	l.addEventListener("change", function (evt) {
		disp.lightness = evt.srcElement.value;
		disp.update();
	});
	
	disp.update();
	
	return disp;	
}

