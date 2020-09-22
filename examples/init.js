//Include NodeSDL module
var NodeSDL;
if (process.env.DEBUG) {
	NodeSDL = require('../build/Debug/NodeSDL.node')
} else {
	NodeSDL = require('../build/Release/NodeSDL.node')
}

//Create window instance
let win = new NodeSDL.Window("DEMO OF NODESDL", 750, 750);

//Start drawing window
win.createWin();