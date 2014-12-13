#include "TextureLoader.hpp"

#include <GL/glew.h>

#include <nim/stb_image.h>

#include <utility>

std::map<Path, Texture> TextureLoader::textureCache = {};

Texture TextureLoader::getTexture(const Path& path) {
	auto iter = textureCache.find(path);
	if (iter != textureCache.end()) {
		return iter->second;
	}

	int width, height, bytes;
	unsigned char* data = stbi_load(path.str().c_str(), &width, &height, &bytes, 0);

	Texture texture = uploadTexture(data, width, height, bytes);
	texture.width = width;
	texture.height = height;
	textureCache.insert(std::make_pair(path, texture));

	return texture;
}

Texture TextureLoader::uploadTexture(unsigned char* data, int width, int height, int bytes) {
	Texture texture;

	GLuint handle;
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);

	if (bytes == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	if (bytes == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	texture.handle = handle;

	return texture;
}
