#ifndef VECTOR2F_HPP
#define VECTOR2F_HPP

class Vector2f {
public:
	float x, y;

	Vector2f();
	Vector2f(float x, float y);
	void set(Vector2f v);
	Vector2f* add(Vector2f v);
	Vector2f* sub(Vector2f v);
	Vector2f* scale(float scale);
	Vector2f* normalise();
	float length();

	void load(float* buf);
	void store(float* buf);
};

Vector2f add(const Vector2f& v1, const Vector2f& v2);
Vector2f sub(const Vector2f& v1, const Vector2f& v2);
Vector2f scale(const Vector2f& v, float scale);
float dot(const Vector2f& v1, const Vector2f& v2);
Vector2f negate(const Vector2f& v);

Vector2f operator+(const Vector2f& v1, const Vector2f& v2);
Vector2f operator-(const Vector2f& v1, const Vector2f& v2);
Vector2f operator*(const Vector2f& v1, float scale);

#endif /* VECTOR2F_HPP */
