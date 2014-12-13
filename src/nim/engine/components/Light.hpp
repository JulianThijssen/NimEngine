#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <nim/engine/core/math/Vector3f.hpp>

class Light : public Component {
public:
	Light() : color(1, 1, 1), attenuation(0.1, 0.25, 0.008) {}

	Vector3f color;
	Vector3f attenuation;
};

#endif /* LIGHT_HPP */
