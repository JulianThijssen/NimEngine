#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <nim/engine/components/Component.hpp>
#include <nim/Engine/components/Transform.hpp>
#include <nim/Engine/components/Mesh.hpp>
#include <nim/Engine/components/Light.hpp>
#include <nim/Engine/components/Camera.hpp>

class Entity {
public:
	Entity();

	Transform* transform = nullptr;
	Mesh* mesh = nullptr;
	Light* light = nullptr;
	Camera* camera = nullptr;
};

#endif /* ENTITY_HPP */
