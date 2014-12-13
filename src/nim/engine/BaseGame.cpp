#include "BaseGame.hpp"

#include <nim/engine/core/diag/Log.hpp>
#include <iostream>

void BaseGame::loadWindow() {
	window.create("Nim Engine", 800, 800);
}

void BaseGame::start() {
	renderer.create();
	update();
}

void BaseGame::update() {
	SDL_Event event;
	unsigned int nextUpdate = SDL_GetTicks();
	unsigned int lastFpsCount = SDL_GetTicks();
	unsigned int frames = 0;
	unsigned int fps = 0;

	while(!window.isClosed()) {
		if (currentScene != nullptr) {
			unsigned int skipped = 0;

			if (SDL_GetTicks() - lastFpsCount > 1000) {
				lastFpsCount = SDL_GetTicks();
				fps = frames;

				std::cout << "FPS: " << fps << std::endl;
				frames = 0;
			}

			while (SDL_GetTicks() > nextUpdate && skipped < MAX_SKIP) {
				while (SDL_PollEvent(&event)) {
					// Event handling
					if(event.type == SDL_QUIT) {
						window.close();
					}
				}
				currentScene->update();
				nextUpdate += SKIP_TIME;
				skipped++;
			}

			renderer.update(*currentScene);
			window.update();
			frames++;
		}
	}
	close();
}

void BaseGame::close() {
	delete currentScene;
	window.close();
}

void BaseGame::addScene(Scene* scene) {
	scenes.push_back(scene);
}

void BaseGame::setScene(Scene* scene) {
	for(auto s: scenes) {
		if(scene == s) {
			currentScene = s;
			currentScene->start();
		}
	}
}
