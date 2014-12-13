#include "Shader.hpp"

Shader::Shader(GLuint handle) {
	this->handle = handle;

	glUseProgram(handle);
	loadUniformLocations();
	glUseProgram(0);
}

void Shader::loadUniformLocations() {
	projLoc = glGetUniformLocation(handle, "projectionMatrix");
	viewLoc = glGetUniformLocation(handle, "viewMatrix");
	modelLoc = glGetUniformLocation(handle, "modelMatrix");
}
