#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <nim/engine/core/math/Vector3f.hpp>

class Transform : public Component {
public:
	Vector3f position;
	Vector3f rotation;
	Vector3f scale;

	Transform() :
		position(0, 0, 0),
		rotation(0, 0, 0),
		scale(1, 1, 1) {}
	Transform(float x, float y, float z) :
		position(x, y, z),
		rotation(0, 0, 0),
		scale(1, 1, 1) {}
};

#endif /* TRANSFORM_HPP */
