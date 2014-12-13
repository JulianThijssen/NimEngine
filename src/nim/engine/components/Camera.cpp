#include "Camera.hpp"

#include <nim/engine/Window.hpp>
#include <nim/engine/core/math/Math.hpp>
#include <math.h>

Camera::Camera(float fovy, float aspect, float zNear, float zFar) :
fovy(fovy), aspect(aspect), zNear(zNear), zFar(zFar) {
	recalculate();
}

void Camera::recalculate() {
	float aspect = (float) Window::width / Window::height;

	projectionMatrix.setIdentity();
	if(perspective) {
		float fovyr = Math::toRadians(fovy);
		projectionMatrix.array[0] = (float) (1 / tan(fovyr / 2)) / aspect;
		projectionMatrix.array[5] = (float) (1 / tan(fovyr / 2));
		projectionMatrix.array[10] = (zNear + zFar) / (zNear - zFar);
		projectionMatrix.array[11] = -1;
		projectionMatrix.array[14] = (2 * zNear * zFar) / (zNear - zFar);
		projectionMatrix.array[15] =- 0;
	} else {
		projectionMatrix.array[0] = 2 / (right - left);
		projectionMatrix.array[5] = 2 / (top - bottom);
		projectionMatrix.array[10] = -2 / (zFar - zNear);
		projectionMatrix.array[12] = (left - right) / (right - left);
		projectionMatrix.array[13] = (bottom - top) / (top - bottom);
		projectionMatrix.array[14] = (zNear - zFar) / (zFar - zNear);
	}
}

Matrix4f Camera::getProjectionMatrix() {
	return projectionMatrix;
}

void Camera::setPerspective() {
	perspective = true;
	recalculate();
}

void Camera::setOrthographic() {
	perspective = false;
	recalculate();
}


void Camera::setFovy(float fovy) {
	this->fovy = fovy;
	recalculate();
}

void Camera::setAspect(float aspect) {
	this->aspect = aspect;
	recalculate();
}

void Camera::setZNear(float zNear) {
	this->zNear = zNear;
	recalculate();
}

void Camera::setZFar(float zFar) {
	this->zFar = zFar;
	recalculate();
}
