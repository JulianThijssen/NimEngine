#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <string>

class Window {
public:
	Window();
	void create(const std::string& title, int width, int height);
	void update();
	void close();

	bool isClosed() const;

	static int width;
	static int height;
private:
	std::string title;
	bool closed;

	SDL_Window* window;
	SDL_GLContext gl_context;

	const static int DEFAULT_WIDTH;
	const static int DEFAULT_HEIGHT;
};

#endif /* WINDOW_HPP */
