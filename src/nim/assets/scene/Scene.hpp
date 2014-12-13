#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <nim/engine/Entity.hpp>

class Scene {
public:
	Scene();
	void start();
	void update();
	void addEntity(const Entity& e);
	const std::vector<Entity>& getEntities() const;

	Entity mainCamera;
private:
	std::vector<Entity> entities;
};

#endif /* SCENE_HPP */
