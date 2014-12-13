#ifndef MATRIX4F_HPP
#define MATRIX4F_HPP

#include <nim/engine/core/math/Vector3f.hpp>

#include <string>

class Matrix4f {
public:
	Matrix4f();
	void setIdentity();
	void translate(const Vector3f& v);
	void rotate(float angle, float x, float y, float z);
	void rotate(const Vector3f& euler);
	void scale(const Vector3f& scale);
	Vector3f transform(const Vector3f& v);
	const float* toArray();
	const std::string str();

	float array[16];
};

#endif /* MATRIX4F_HPP */
