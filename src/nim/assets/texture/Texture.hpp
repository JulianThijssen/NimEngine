#ifndef TEXTURE_HPP
#define TEXTURE_HPP

class Texture {
public:
	unsigned int getWidth() { return width; }
	unsigned int getHeight() { return height; }

	unsigned int handle;
private:
	unsigned int width;
	unsigned int height;
};

#endif /* TEXTURE_HPP */
