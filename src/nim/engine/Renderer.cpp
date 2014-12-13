#include "Renderer.hpp"
#include <GL/glew.h>

#include <nim/assets/scene/Scene.hpp>
#include <nim/assets/shader/ShaderLoader.hpp>

#include <nim/engine/Entity.hpp>
#include <nim/engine/components/Mesh.hpp>
#include <nim/engine/components/Light.hpp>
#include <nim/engine/core/diag/Log.hpp>
#include <cstdio>
#include <sstream>

Renderer::Renderer() {

}

void Renderer::create() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClearColor(0, 0, 0.4, 1.0);

	handle = ShaderLoader::loadShaders("res/shaders/diffuse.vert", "res/shaders/diffuse.frag");
}

void Renderer::update(Scene& scene) {
	// Render
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(handle);

	projectionMatrix = scene.mainCamera.camera->getProjectionMatrix();

	int projLoc = glGetUniformLocation(handle, "projectionMatrix");
	int viewLoc = glGetUniformLocation(handle, "viewMatrix");
	int modelLoc = glGetUniformLocation(handle, "modelMatrix");

	glUniformMatrix4fv(projLoc, 1, false, projectionMatrix.toArray());
	glUniformMatrix4fv(viewLoc, 1, false, viewMatrix.toArray());
	glUniformMatrix4fv(modelLoc, 1, false, modelMatrix.toArray());

	std::vector<Entity> lights;
	for(const auto& entity: scene.getEntities()) {
		if(entity.transform != nullptr && entity.light != nullptr) {
			lights.push_back(entity);
		}
	}

	uploadLights(handle, lights);

	for(const auto& entity: scene.getEntities()) {
		if(entity.transform != nullptr && entity.mesh != nullptr) {
			Transform transform = *entity.transform;
			modelMatrix.setIdentity();
			modelMatrix.translate(transform.position);
			modelMatrix.rotate(transform.rotation);
			modelMatrix.scale(transform.scale);

			drawMesh(*entity.mesh);
		}
	}
}

void Renderer::uploadLights(int shader, std::vector<Entity> lights) {
	int numLightsLoc = glGetUniformLocation(shader, "numLights");
	glUniform1i(numLightsLoc, lights.size());

	for(unsigned int i = 0; i < lights.size(); i++) {
		Entity e = lights[i];
		const Transform& transform = *e.transform;
		const Light& light = *e.light;

		char attribute[30];
		snprintf(attribute, sizeof(attribute), "%s%d%s", "lights[", i, "].position");
		int lightPos = glGetUniformLocation(shader, attribute);
		snprintf(attribute, sizeof(attribute), "%s%d%s", "lights[", i, "].color");
		int lightColor = glGetUniformLocation(shader, attribute);
		snprintf(attribute, sizeof(attribute), "%s%d%s", "lights[", i, "].attenuation");
		int lightAtt = glGetUniformLocation(shader, attribute);

		glUniform3f(lightPos, transform.position.x, transform.position.y, transform.position.z);
		glUniform3f(lightColor, light.color.x, light.color.y, light.color.z);
		glUniform3f(lightAtt, light.attenuation.x, light.attenuation.y, light.attenuation.z);
	}
}

void Renderer::drawMesh(const Mesh& mesh) {
	glBindVertexArray(mesh.handle);
	glDrawArrays(GL_TRIANGLES, 0, mesh.numFaces * 3);

	glBindVertexArray(0);
}
