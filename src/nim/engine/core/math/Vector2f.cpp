#include "Vector2f.hpp"
#include <cmath>

Vector2f::Vector2f() : x(0), y(0) {}

Vector2f::Vector2f(float x, float y) : x(x), y(y) {}

void Vector2f::set(Vector2f v) {
	x = v.x;
	y = v.y;
}

Vector2f* Vector2f::add(Vector2f v) {
	x += v.x;
	y += v.y;
	return this;
}

Vector2f* Vector2f::sub(Vector2f v) {
	x -= v.x;
	y -= v.y;
	return this;
}

Vector2f* Vector2f::scale(float scale) {
	x *= scale;
	y *= scale;
	return this;
}

Vector2f* Vector2f::normalise() {
	float l = length();
	x /= l;
	y /= l;
	return this;
}

float Vector2f::length() {
	return sqrt(pow(x, 2) + pow(y, 2));
}

void Vector2f::load(float* buf) {
	x = buf[0];
	y = buf[1];
}

void Vector2f::store(float* buf) {
	buf[0] = x;
	buf[1] = y;
}

Vector2f add(const Vector2f& v1, const Vector2f& v2) {
	Vector2f v;
	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	return v;
}

Vector2f sub(const Vector2f& v1, const Vector2f& v2) {
	Vector2f v;
	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	return v;
}

Vector2f scale(const Vector2f& v, float scale) {
	Vector2f vs;
	vs.x = v.x * scale;
	vs.y = v.y * scale;
	return vs;
}

float dot(const Vector2f& v1, const Vector2f& v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

Vector2f negate(const Vector2f& v) {
	Vector2f vn;
	vn.x = -v.x;
	vn.y = -v.y;
	return vn;
}

Vector2f operator+(const Vector2f& v1, const Vector2f& v2) {
  Vector2f v;
  v.x = v1.x + v2.x;
  v.y = v1.y + v2.y;
  return v;
}

Vector2f operator-(const Vector2f& v1, const Vector2f& v2) {
  Vector2f v;
  v.x = v1.x - v2.x;
  v.y = v1.y - v2.y;
  return v;
}

Vector2f operator*(const Vector2f& v, float scale) {
  Vector2f vs;
  vs.x = v.x * scale;
  vs.y = v.y * scale;
  return vs;
}
