#include "Window.hpp"
#include <GL/glew.h>
#include <iostream>
#include <cstdlib>

const int Window::DEFAULT_WIDTH = 1024;
const int Window::DEFAULT_HEIGHT = 768;

int Window::width = DEFAULT_WIDTH;
int Window::height = DEFAULT_HEIGHT;

Window::Window() : gl_context(0), closed(true) {

}

void Window::create(const std::string& title, int width, int height) {
	this->title = title;
	Window::width = width;
	Window::height = height;

	SDL_Init(SDL_INIT_VIDEO);

	unsigned int flags = SDL_WINDOW_OPENGL;

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

	gl_context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLuint glewInitReturnValue = glewInit();

	if (glewInitReturnValue != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		std::exit(1);
	}
	if (not GLEW_VERSION_2_1) {
		std::cout << "GLEW version 2.1 is unsupported" << std::endl;
		std::exit(1);
	}

	SDL_GL_SetSwapInterval(0);

	closed = false;
}

void Window::update() {
	SDL_GL_SwapWindow(window);
}

bool Window::isClosed() const {
	return closed;
}

void Window::close() {
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
	closed = true;
}
