#ifndef SHADERLOADER_HPP
#define SHADERLOADER_HPP

#include <string>

class ShaderLoader {
public:
	static int loadShaders(std::string vertPath, std::string fragPath);
	static int loadShader(std::string path, int type);
};

#endif /* SHADERLOADER_HPP */
