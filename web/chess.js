
const NUM_TILES = 8;
const GAME_SIZE = 400;
const TILE_SIZE = GAME_SIZE / NUM_TILES;

// DOM Style Helpers
function setAttributes(element, props) {
	for (var prop in props) {
		element.setAttribute(prop, props[prop]);
	}
}

function setPosition(top, left) {
	return "top: " + (top * TILE_SIZE) + "px;left: " + (left * TILE_SIZE) + "px;";
}

// Animation helpers
function animate(elemId, update) {
	var elem = document.getElementById(elemId);
	if (!elem) return;
	var progress = 0;
	var id = setInterval(progressFn, id);
	var progressFn = function () {
		if (progress == 100) {
			clearInterval(id);
			return;
		}
		progress++;
		update(elem, progress);
	}
}

function moveElement(elemId, srcR, srcC, destR, destC) {
	var update = function(elem, progress) {
		elem.style.top  = (srcR + (destR - srcR) * progress / 100.0) + "px";
		elem.style.left = (srcC + (destC - srcC) * progress / 100.0) + "px";
	}
	animate(elemId, update);
}

function fadeOut(elemId) {
	var update = function(elem, progress) {
		elem.style.opacity = (100 - progress)/100.0;
	}
	animate(elemId, update);
}

function fadeIn(elemId) {
	var update = function(elem, progress) {
		elem.style.opacity = progress/100.0;
	}
	animate(elemId, update);
}

// Game functions

function handleMove(evt) {
	var id = evt.srcElement.id;
	var r = parseInt(id[id.length - 2]);
	var c = parseInt(id[id.length - 1]);
	this.moveTo(r, c);
}

function canMoveTo(r, c) {
	var dispR = Math.abs(r - this.posR);
	var dispC = Math.abs(c - this.posC);
	return ((dispR === this.a && dispC === this.b) || 
		(dispR === this.b && dispC === this.a)) && !this.captured;
}

function moveTo(r, c) {
	if (!this.canMoveTo(r,c)) {
		return false;
	}

	var srcR = this.posR * 50;
	var srcC = this.posC * 50;
	var destR = r * 50;
	var destC = c * 50;

	var piece = document.getElementById(this.id + "wknight");
	
	var progress = 0;
	var id = setInterval(frame, 3);
	function frame() {
		if (progress == 100) {
			clearInterval(id);
			return;
		}
		progress++;
		piece.style.top  = (srcR + (destR - srcR) * progress / 100.0) + "px";
		piece.style.left = (srcC + (destC - srcC) * progress / 100.0) + "px";
	}

	this.posR = r;
	this.posC = c;
	return true;
}

function capture() {
	if (!this.moveTo(this.endR, this.endC)) {
		return;
	}
	var progress = 0;
	var id = setInterval(frame, 3);
	var gameId = this.id;
	function frame() {
		if (progress == 100) {
			clearInterval(id);
			return;
		}
		progress++;
		document.getElementById(gameId + "bknight").style.opacity = (100 - progress)/100.0;
	}
	this.captured = true;
}

function newGame() {
	this.posR = this.startR;
	this.posC = this.startC;
	this.captured = false;
}

// Main
function createGame(divId, options) {
	let root = document.getElementById(divId);
	if (!root) return {};
	
	let game = options;
	game.id = divId;
	game.canMoveTo = canMoveTo;
	game.moveTo = moveTo;
	game.capture = capture;
	game.newGame = newGame;

	game.newGame();

	var tile;
	for (var r = 0; r < NUM_TILES; r++) {
		for (var c = 0; c < NUM_TILES; c++) {
			tile = document.createElement("div");
			setAttributes(tile, {
				"class": "tile " + ((r+c)%2 ? "bt" : "wt"),
				"style": setPosition(r, c),
				"id": game.id + "tile" + r + c
			});
			tile.onclick = handleMove.bind(game);
			root.appendChild(tile);
		}
	}
	
	let bknight = document.createElement("img");
	setAttributes(bknight, {
		"class": "tile",
		"style": setPosition(game.endR, game.endC),
		"id": game.id + "bknight",
		"src": "https://upload.wikimedia.org/wikipedia/commons/2/21/Western_black_side_Knight.svg" 
	});
	bknight.onclick = game.capture.bind(game);
	root.appendChild(bknight);
	
	let wknight = document.createElement("img");
	setAttributes(wknight, {
		"class": "tile",
		"style": setPosition(game.startR, game.startC),
		"id": game.id + "wknight",
		"src": "https://upload.wikimedia.org/wikipedia/commons/c/c3/Western_white_side_Knight.svg" 
	});
	root.appendChild(wknight);
}
