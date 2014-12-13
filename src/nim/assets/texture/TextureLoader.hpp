#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

#include <nim/assets/texture/Texture.hpp>
#include <nim/engine/core/file/Path.hpp>
#include <map>

class TextureLoader {
public:
	static Texture getTexture(const Path& path);
private:
	static Texture uploadTexture(unsigned char* data, int width, int height, int bytes);

	static std::map<Path, Texture> textureCache;
};

#endif /* TEXTURELOADER_HPP */
