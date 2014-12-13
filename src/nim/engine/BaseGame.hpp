#ifndef BASEGAME_H
#define BASEGAME_H

#include <nim/engine/Window.hpp>
#include <nim/engine/Renderer.hpp>
#include <nim/assets/scene/Scene.hpp>
#include <vector>

class BaseGame {
public:
	void loadWindow();
	void start();
	void close();
	void addScene(Scene* scene);
	void setScene(Scene* scene);
private:
	void update();

	Window window;
	Renderer renderer;

	std::vector<Scene*> scenes;
	Scene* currentScene;

	const unsigned int UPDATE_RATE = 25;
	const unsigned int SKIP_TIME = 40;
	const unsigned int MAX_SKIP = 15;
};

#endif /* BASEGAME_H */
