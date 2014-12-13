#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <nim/engine/core/math/Vector3f.hpp>
#include <nim/assets/texture/Texture.hpp>
#include <string>

class Material {
public:
	Vector3f diffuseColor;
	Vector3f specularColor;
	Vector3f ambientColor;

	Texture* diffuse  = nullptr;
	Texture* normal   = nullptr;
	Texture* specular = nullptr;

	Material(std::string name) :
		name(name),
		diffuseColor(1, 1, 1),
		specularColor(1, 1, 1),
		ambientColor(1, 1, 1) {}
	std::string getName();
private:
	std::string name;
};


#endif /* MATERIAL_HPP */
