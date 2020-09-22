#include <nan.h>
#include <SDL2/SDL.h>
#include <string>

#ifndef _NODESDL_H
#define _NODESDL_H 1

namespace NodeSDL {
	/**
	 * SDL Window wrapper
	 */
	class Window : public Nan::ObjectWrap {
	public:
		/**
		 * Variables
		 */
		std::string title;

		/**
		 * Node module construction
		 */
		static NAN_MODULE_INIT(Init);
		static NAN_METHOD(New);
		static Nan::Persistent<v8::Function> constructor;

		/**
		 * SDL implementations
		 */
		static NAN_METHOD(CreateWin);

		/**
		 * Class initalizer
		 */
		Window();
		~Window();

	private:
		/**
		 * Variables
		 */
		SDL_Window* win;
		SDL_Surface* surface;

		double width;
		double height;
	};
};

#endif //_NODESDL_H