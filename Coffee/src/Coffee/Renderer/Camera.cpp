#include "CoffeePCH.h"
#include "Coffee/Renderer/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace Coffee;

OrthographicCamera::OrthographicCamera(const float left, const float right, const float bottom, const float top) :
	_projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), _viewMatrix(glm::mat4(1.0f)) {
	_viewProjection = _projectionMatrix * _viewMatrix;
}

void OrthographicCamera::setProjection(const float left, const float right, const float bottom, const float top) {
	_projectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	_viewProjection = _projectionMatrix * _viewMatrix;
}

const glm::vec3& OrthographicCamera::getPosition() const { return _position; }
void OrthographicCamera::setPosition(const glm::vec3& position) {
	_position = position;
	viewMatrixCalc();
}
void OrthographicCamera::setPosition(const float x, const float y, const float z) { setPosition(glm::vec3(x, y, z)); }

float OrthographicCamera::getRotation() const { return _rotation; }
void OrthographicCamera::setRotation(const float rotation) {
	_rotation = rotation;
	viewMatrixCalc();
}

const glm::mat4& OrthographicCamera::getProjectionMatrix() const { return _projectionMatrix; }
const glm::mat4& OrthographicCamera::getViewMatrix() const { return _viewMatrix; }
const glm::mat4& OrthographicCamera::getViewProjectionMatrix() const { return _viewProjection; }

void OrthographicCamera::viewMatrixCalc() {
	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0.0f, 0.0f, 1.0f));

	_viewMatrix = glm::inverse(transform);
	_viewProjection = _projectionMatrix * _viewMatrix;
}
