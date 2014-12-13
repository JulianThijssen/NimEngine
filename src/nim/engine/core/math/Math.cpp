#include "Math.hpp"

const float Math::PI = 3.14159265359;

float Math::toDegrees(float radians) {
	return radians * (180 / PI);
}

float Math::toRadians(float degrees) {
	return degrees * (PI / 180);
}
