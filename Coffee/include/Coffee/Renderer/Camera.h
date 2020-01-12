#pragma once

#include <glm/glm.hpp>

namespace Coffee {

	class OrthographicCamera {
	public:
		
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera() = default;

		void setProjection(float left, float right, float bottom, float top);

		const glm::vec3& getPosition() const;
		void setPosition(const glm::vec3& position);
		void setPosition(float x, float y, float z);

		float getRotation() const;
		void setRotation(float rotation);

		const glm::mat4& getProjectionMatrix() const;
		const glm::mat4& getViewMatrix() const;
		const glm::mat4& getViewProjectionMatrix() const;
		
	private:

		void viewMatrixCalc();

		glm::vec3 _position = { 0.0f, 0.0f, 0.0f };
		float _rotation = 0.0f;
		
		glm::mat4 _projectionMatrix;
		glm::mat4 _viewMatrix;
		glm::mat4 _viewProjection;

	};
}
