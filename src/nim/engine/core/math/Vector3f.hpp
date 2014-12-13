#ifndef VECTOR3F_HPP
#define VECTOR3F_HPP

#include <string>

class Vector3f {
public:
	float x, y, z;

	Vector3f();
	Vector3f(float x, float y, float z);
	void set(float x, float y, float z);
	void set(Vector3f v);
	Vector3f* add(Vector3f v);
	Vector3f* sub(Vector3f v);
	Vector3f* scale(float scale);
	Vector3f* normalise();
	float length();

	void load(float* buf);
	void store(float* buf);

	const std::string str() const;
};

Vector3f add(const Vector3f& v1, const Vector3f& v2);
Vector3f sub(const Vector3f& v1, const Vector3f& v2);
Vector3f scale(const Vector3f& v, float scale);
float dot(const Vector3f& v1, const Vector3f& v2);
Vector3f cross(const Vector3f& v1, const Vector3f& v2);
Vector3f negate(const Vector3f& v);

Vector3f operator+(const Vector3f& v1, const Vector3f& v2);
Vector3f operator-(const Vector3f& v1, const Vector3f& v2);
Vector3f operator*(const Vector3f& v1, float scale);

#endif /* VECTOR3F_HPP */
