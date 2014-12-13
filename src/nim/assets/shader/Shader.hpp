#ifndef SHADER_HPP
#define SHADER_HPP

#include <GL/glew.h>

class Shader {
public:
	GLuint handle;

	GLuint projLoc;
	GLuint viewLoc;
	GLuint modelLoc;

	Shader(GLuint handle);
	void loadUniformLocations();
};



#endif /* SHADER_HPP */
