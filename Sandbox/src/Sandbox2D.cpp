#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

Sandbox2D::Sandbox2D() :
	Layer("Sandbox 2D"),
	cameraController(static_cast<float>(Coffee::Application::getInstance().getWindow().getWidth()) / static_cast<float>(Coffee::Application::getInstance().getWindow().getHeight()))
{}

void Sandbox2D::onPush() {
	CF_PROFILE_FUNCTION();
	
	checkerboardTexture = Coffee::Texture2D::create("assets/textures/checkerboard.png");
	Coffee::RenderCommand::setClearColour(0.1f, 0.1f, 0.1f, 1.0f);
}

void Sandbox2D::onPop() {
	CF_PROFILE_FUNCTION();
}

void Sandbox2D::update(const Coffee::Timestep ts) {
	CF_PROFILE_FUNCTION();
	
	cameraController.onUpdate(ts);

	Coffee::Renderer2D::beginScene(cameraController.getCamera());
	{		
		static float rotation = 0.0f;
		rotation += ts * 50.0f;
		
		Coffee::Renderer2D::drawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Coffee::Renderer2D::drawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Coffee::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.2f }, { 10.0f, 10.0f }, checkerboardTexture, { 1.0f, 1.0f, 1.0f, 1.0f }, 10.0f);

		Coffee::Renderer2D::drawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -rotation, { 0.8f, 0.2f, 0.3f, 1.0f });
		Coffee::Renderer2D::drawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 1.5f, 1.5f }, rotation, checkerboardTexture, { 0.2f, 0.8f, 0.3f, 1.0f }, 1.0f);
	}
	Coffee::Renderer2D::endScene();
	
}
void Sandbox2D::drawImgui() {
	CF_PROFILE_FUNCTION();
	
	ImGui::Begin(getName().c_str());
	ImGui::ColorEdit4("Square colour", glm::value_ptr(squareColour));
	ImGui::End();
}

void Sandbox2D::onEvent(Coffee::Event& e) {
	cameraController.onEvent(e);
}
