#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <nim/engine/components/Component.hpp>
#include <nim/engine/core/math/Matrix4f.hpp>

const bool DEFAULT_PERSPECTIVE = true;
const float DEFAULT_FOVY = 90;
const float DEFAULT_ASPECT = 1;
const float DEFAULT_ZNEAR = 0.1f;
const float DEFAULT_ZFAR = 100;

const float DEFAULT_TOP = 0.5f;
const float DEFAULT_BOTTOM = -0.5f;
const float DEFAULT_LEFT = -0.5f;
const float DEFAULT_RIGHT = 0.5f;


class Camera : public Component {
public:
	Camera() {
		recalculate();
	}
	Camera(float fovy, float aspect, float zNear, float zFar);
	void recalculate();
	Matrix4f getProjectionMatrix();
	void setPerspective();
	void setOrthographic();

	void setFovy(float fovy);
	void setAspect(float aspect);
	void setZNear(float zNear);
	void setZFar(float zFar);

private:
	Matrix4f projectionMatrix;
	bool perspective = DEFAULT_PERSPECTIVE;
	float fovy   = DEFAULT_FOVY;
	float aspect = DEFAULT_ASPECT;
	float zNear  = DEFAULT_ZNEAR;
	float zFar   = DEFAULT_ZFAR;

	float top    = DEFAULT_TOP;
	float bottom = DEFAULT_BOTTOM;
	float left   = DEFAULT_LEFT;
	float right  = DEFAULT_RIGHT;
};

#endif /* CAMERA_HPP */
