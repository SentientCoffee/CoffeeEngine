#include "Sandbox2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>
#include <Coffee/Renderer/Texture.h>
#include <Coffee/Renderer/Renderer2D.h>

Sandbox2D::Sandbox2D() :
	Layer("Sandbox 2D"),
	cameraController(static_cast<float>(Coffee::Application::getInstance().getWindow().getWidth()) / static_cast<float>(Coffee::Application::getInstance().getWindow().getHeight())) {}

void Sandbox2D::onPush() {
	checkerboardTexture = Coffee::Texture2D::create("assets/textures/checkerboard.png");
	Coffee::RenderCommand::setClearColour(0.1f, 0.1f, 0.1f, 1.0f);
}

void Sandbox2D::onPop() {}

void Sandbox2D::update(const Coffee::Timestep ts) {
	cameraController.onUpdate(ts);

	#if 0
	Coffee::ColouredQuad imguiQuad = {
		{ -1.0f, 0.0f },
		{ 0.8f, 0.8f },
		squareColour
	};

	Coffee::ColouredQuad redQuad = {
		{ 0.5f, -0.5f },
		{ 0.5f, 0.75f },
		{ 0.8f, 0.2f, 0.3f, 1.0f }
	};

	Coffee::TexturedQuad checkerboard = {
		{ 0.0f, 0.0f, -0.1f },
		{ 10.0f, 10.0f },
		checkerboardTexture,
		{ 0.2f, 0.8f, 0.3f, 1.0f }
	};
	#endif


	Coffee::Renderer2D::beginScene(cameraController.getCamera());
	{
		// Coffee::Renderer2D::drawQuad(imguiQuad);
		// Coffee::Renderer2D::drawQuad(redQuad);
		// Coffee::Renderer2D::drawQuad(checkerboard);
		Coffee::Renderer2D::drawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Coffee::Renderer2D::drawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	}
	Coffee::Renderer2D::endScene();
	
}
void Sandbox2D::drawImgui() {
	ImGui::Begin(getName().c_str());
	ImGui::ColorEdit4("Square colour", glm::value_ptr(squareColour));
	ImGui::End();
}

void Sandbox2D::onEvent(Coffee::Event& e) {
	cameraController.onEvent(e);
}
