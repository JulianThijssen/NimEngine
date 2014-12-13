#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <nim/assets/shader/Shader.hpp>
#include <nim/engine/core/math/Matrix4f.hpp>
#include <vector>

class Scene;
class Entity;
class Mesh;
class Light;

class Renderer {
public:
	Renderer();
	void create();
	void update(Scene& scene);
	void uploadLights(std::vector<Entity> lights);
	void drawMesh(const Mesh& mesh);
private:
	Matrix4f projectionMatrix;
	Matrix4f viewMatrix;
	Matrix4f modelMatrix;

	Shader* shader = nullptr;
};

#endif /* RENDERER_HPP */
