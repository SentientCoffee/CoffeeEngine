#pragma once

#include "Coffee/Core/Timestep.h"

#include "Coffee/Events/AppEvents.h"
#include "Coffee/Events/MouseEvents.h"

#include "Coffee/Renderer/Camera.h"

namespace Coffee {

	class OrthographicCameraController {
	public:

		OrthographicCameraController(float aspectRatio, bool rotation = false);
		~OrthographicCameraController() = default;
		

		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		OrthographicCamera& getCamera();
		const OrthographicCamera& getCamera() const;

	private:

		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onWindowResized(WindowResizedEvent& e);

		float _aspectRatio = 0.0f;
		float _zoom = 1.0f;

		OrthographicCamera _camera;
		
		glm::vec3 _cameraPosition = { 0.0f, 0.0f, 0.0f };
		float _camTranslationSpeed = 5.0f;
		
		bool _rotation = false;
		float _cameraRotation = 0.0f;
		float _camRotationSpeed = 180.0f;
	};
	
}
