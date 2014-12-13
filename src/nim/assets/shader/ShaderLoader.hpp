#ifndef SHADERLOADER_HPP
#define SHADERLOADER_HPP

#include <nim/assets/shader/Shader.hpp>

#include <string>

class ShaderLoader {
public:
	static Shader* loadShaders(std::string vertPath, std::string fragPath);
	static int loadShader(std::string path, int type);
};

#endif /* SHADERLOADER_HPP */
