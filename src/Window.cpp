#include "NodeSDL.hh"

/**
 * FUTURE:
 * Use doxygen for documentation
 * Reference:
 * 	https://medium.com/netscape/tutorial-building-native-c-modules-for-node-js-using-nan-part-1-755b07389c7c
 */


//Initalize constructor
Nan::Persistent<v8::Function> NodeSDL::Window::constructor;

/**
 * Module initalization
 */
//Window class
NAN_MODULE_INIT(NodeSDL::Window::Init) {
	//Class constructor template
	v8::Local<v8::FunctionTemplate> WindowTmpl = Nan::New<v8::FunctionTemplate>(New);
	WindowTmpl->SetClassName(Nan::New("Window").ToLocalChecked());
	WindowTmpl->InstanceTemplate()->SetInternalFieldCount(1);

	//Add methods to class
	Nan::SetPrototypeMethod(WindowTmpl, "createWin", CreateWin);

	//Export class
	constructor.Reset(Nan::GetFunction(WindowTmpl).ToLocalChecked());
	Nan::Set(target, Nan::New("Window").ToLocalChecked(), Nan::GetFunction(WindowTmpl).ToLocalChecked());
}



/**
 * JS class intializer
 */
NAN_METHOD(NodeSDL::Window::New) {
	//Get context of function
	v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();

	//Create instance of object to use
	NodeSDL::Window* thisWin = new Window();

	//Only allow as 'new Window()' and not 'Window()'
	if(!info.IsConstructCall())
		return Nan::ThrowError(Nan::New("Please use the 'new' operator.").ToLocalChecked());

	//Parse arguments
	switch(info.Length()) {
		//new Window("title");
		case 1:
			if(info[0]->IsString()) {
				v8::String::Utf8Value v8Title(info.GetIsolate(), info[0]);
				thisWin->title = std::string(*v8Title);
			} else
				return Nan::ThrowError(Nan::New("Expected a string.").ToLocalChecked());
			thisWin->height = 400;
			thisWin->width = 400;
			break;
		//new Window(200, 600);
		case 2:
			if(info[0]->IsNumber() && info[1]->IsNumber()) {
				thisWin->height = info[0]->NumberValue(context).FromJust();
				thisWin->width = info[1]->NumberValue(context).FromJust();
			} else
				return Nan::ThrowError(Nan::New("Expected two numbers.").ToLocalChecked());
			thisWin->title = "NodeSDL Window";
			break;
		//new Window("title", 200, 600);
		case 3:
			if(info[0]->IsString() && info[1]->IsNumber() && info[2]->IsNumber()) {
				v8::String::Utf8Value v8Title(info.GetIsolate(), info[0]);
				thisWin->title = std::string(*v8Title);
				thisWin->height = info[1]->NumberValue(context).FromJust();
				thisWin->width = info[2]->NumberValue(context).FromJust();
			} else
				return Nan::ThrowError(Nan::New("Expected a string and two numbers.").ToLocalChecked());
			break;
		//new Window();
		default:
			thisWin->title = "NodeSDL Window";
			thisWin->height = 400;
			thisWin->width = 400;
	}

	//Wrap instance to JS object
	thisWin->Wrap(info.Holder());

	//Return JS object
	info.GetReturnValue().Set(info.Holder());
}



/**
 * Class methods
 */
NAN_METHOD(NodeSDL::Window::CreateWin) {
	//Unwrap instance from JS object
	NodeSDL::Window* thisWin = Nan::ObjectWrap::Unwrap<NodeSDL::Window>(info.This());

	//Create window
	thisWin->win = SDL_CreateWindow(thisWin->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, thisWin->width, thisWin->height, SDL_WINDOW_SHOWN);
	if(thisWin->win == NULL)
		return Nan::ThrowError(Nan::New("Unable to create SDL window.").ToLocalChecked());
	else {
		//Grab surface from window
		thisWin->surface = SDL_GetWindowSurface(thisWin->win);
		if(thisWin->surface == NULL)
			return Nan::ThrowError(Nan::New("Unable to create SDL surface.").ToLocalChecked());

		/**
		 * TEST DRAWING
		 */
		//Initial screen update
		SDL_Delay(250);
		//SDL_UpdateWindowSurface(thisWin->win);

		//Draw red
		SDL_FillRect(thisWin->surface, NULL, SDL_MapRGB(thisWin->surface->format, 0xff, 0, 0));
		SDL_UpdateWindowSurface(thisWin->win);

		//Draw green
		SDL_Delay(1000);
		SDL_FillRect(thisWin->surface, NULL, SDL_MapRGB(thisWin->surface->format, 0, 0xff, 0));
		SDL_UpdateWindowSurface(thisWin->win);

		//Draw blue
		SDL_Delay(1000);
		SDL_FillRect(thisWin->surface, NULL, SDL_MapRGB(thisWin->surface->format, 0, 0, 0xff));
		SDL_UpdateWindowSurface(thisWin->win);

		//Fade from black to red and back
		SDL_Delay(1000);
		for(int R = 0; R < 0xff; R++) {
			SDL_FillRect(thisWin->surface, NULL, SDL_MapRGB(thisWin->surface->format, R, 0, 0));
			SDL_UpdateWindowSurface(thisWin->win);
			SDL_Delay(10);
		}
		for(int R = 0xff; R > 0; R--) {
			SDL_FillRect(thisWin->surface, NULL, SDL_MapRGB(thisWin->surface->format, R, 0, 0));
			SDL_UpdateWindowSurface(thisWin->win);
			SDL_Delay(10);
		}

		//Fade from black to green and back
		for(int G = 0; G < 0xff; G++) {
			SDL_FillRect(thisWin->surface, NULL, SDL_MapRGB(thisWin->surface->format, 0, G, 0));
			SDL_UpdateWindowSurface(thisWin->win);
			SDL_Delay(10);
		}
		for(int G = 0xff; G > 0; G--) {
			SDL_FillRect(thisWin->surface, NULL, SDL_MapRGB(thisWin->surface->format, 0, G, 0));
			SDL_UpdateWindowSurface(thisWin->win);
			SDL_Delay(10);
		}

		//Fade from black to blue and back
		for(int B = 0; B < 0xff; B++) {
			SDL_FillRect(thisWin->surface, NULL, SDL_MapRGB(thisWin->surface->format, 0, 0, B));
			SDL_UpdateWindowSurface(thisWin->win);
			SDL_Delay(10);
		}
		for(int B = 0xff; B > 0; B--) {
			SDL_FillRect(thisWin->surface, NULL, SDL_MapRGB(thisWin->surface->format, 0, 0, B));
			SDL_UpdateWindowSurface(thisWin->win);
			SDL_Delay(10);
		}

		//Return true on success
		SDL_Delay(1000);
		info.GetReturnValue().Set(Nan::True());
	}
}



/**
 * C++ class initalizer
 */
NodeSDL::Window::Window() {
	//Initalize variables
	this->win = NULL;
	this->surface = NULL;
	this->width = 0;
	this->height = 0;
}

NodeSDL::Window::~Window() {
	//Destroy SDL instance
	SDL_DestroyWindow(this->win);
	SDL_Quit();
}