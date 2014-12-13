#include "ShaderLoader.hpp"
#include <GL/glew.h>

#include <nim/engine/core/diag/Log.hpp>

#include <fstream>
#include <streambuf>

int ShaderLoader::loadShaders(std::string vertPath, std::string fragPath) {
	int vertexShader = loadShader(vertPath, GL_VERTEX_SHADER);
	int fragmentShader = loadShader(fragPath, GL_FRAGMENT_SHADER);


	int shaderProgram = glCreateProgram();

	char log[1024];
	GLint status;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		glGetShaderInfoLog(vertexShader, 1024, nullptr, log);
		Log::error(log);
	}
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
	if(status == GL_FALSE) {
		glGetShaderInfoLog(fragmentShader, 1024, nullptr, log);
		Log::error(log);
	}

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);

	int handle = shaderProgram;
	return handle;
}

int ShaderLoader::loadShader(std::string path, int type) {
	int handle = 0;

	// Read all lines and append together
	std::ifstream file(path);
	std::string source;

	file.seekg(0, std::ios::end);
	source.reserve(file.tellg());
	file.seekg(0, std::ios::beg);

	source.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	const char* csource = source.c_str();

	// Create the shader
	handle = glCreateShader(type);
	glShaderSource(handle, 1, &csource, NULL);
	glCompileShader(handle);

	return handle;
}
