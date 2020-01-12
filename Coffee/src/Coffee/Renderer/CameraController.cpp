#include "CoffeePCH.h"
#include "Coffee/Renderer/CameraController.h"

#include "Coffee/Input/Input.h"

using namespace Coffee;

OrthographicCameraController::OrthographicCameraController(const float aspectRatio, const bool rotation) :
	_aspectRatio(aspectRatio), _camera(-aspectRatio * _zoom, aspectRatio * _zoom, -_zoom, _zoom), _rotation(rotation) {
	CF_CORE_ASSERT(_aspectRatio, "Aspect ratio needs to be set to non-zero value!");
}

void OrthographicCameraController::onUpdate(const Timestep ts) {
	if(Input::isKeyPressed(KeyCode::A)) {
		_cameraPosition.x -= _camTranslationSpeed * ts;
	}
	else if(Input::isKeyPressed(KeyCode::D)) {
		_cameraPosition.x += _camTranslationSpeed * ts;
	}

	if(Input::isKeyPressed(KeyCode::W)) {
		_cameraPosition.y += _camTranslationSpeed * ts;
	}
	else if(Input::isKeyPressed(KeyCode::S)) {
		_cameraPosition.y -= _camTranslationSpeed * ts;
	}

	if(_rotation) {
		if(Input::isKeyPressed(KeyCode::Q)) {
			_cameraRotation += _camRotationSpeed * ts;
		}
		else if(Input::isKeyPressed(KeyCode::E)) {
			_cameraRotation -= _camRotationSpeed * ts;
		}

		_camera.setRotation(_cameraRotation);
	}

	_camera.setPosition(_cameraPosition);
}

OrthographicCamera& OrthographicCameraController::getCamera() { return _camera; }
const OrthographicCamera& OrthographicCameraController::getCamera() const { return _camera; }

void OrthographicCameraController::onEvent(Event& e) {
	EventDispatcher d(e);
	d.dispatch<MouseScrolledEvent>(CF_BIND_FN(OrthographicCameraController::onMouseScrolled));
	d.dispatch<WindowResizedEvent>(CF_BIND_FN(OrthographicCameraController::onWindowResized));
}

bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e) {
	_zoom -= e.getYOffset() * 0.25f;
	_zoom = glm::max(_zoom, 0.25f);
	_camera.setProjection(-_aspectRatio * _zoom, _aspectRatio * _zoom, -_zoom, _zoom);
	return false;
}

bool OrthographicCameraController::onWindowResized(WindowResizedEvent& e) {
	_aspectRatio = static_cast<float>(e.getWidth()) / static_cast<float>(e.getHeight());
	_camera.setProjection(-_aspectRatio * _zoom, _aspectRatio * _zoom, -_zoom, _zoom);
	return false;
}
