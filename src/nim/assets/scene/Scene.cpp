#include "Scene.hpp"

Scene::Scene() {

}

void Scene::start() {
	// Start scripts
}

void Scene::update() {
	// Update scripts
}

void Scene::addEntity(const Entity& e) {
	entities.push_back(e);
}

const std::vector<Entity>& Scene::getEntities() const {
	return entities;
}
