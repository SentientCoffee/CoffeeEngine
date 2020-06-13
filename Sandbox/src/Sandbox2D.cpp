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

	Coffee::Renderer2D::resetStats();

	Coffee::Renderer2D::beginScene(cameraController.getCamera());
	{		
		static float rotation = 0.0f;
		rotation += ts * 50.0f;
		
		Coffee::Renderer2D::drawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Coffee::Renderer2D::drawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Coffee::Renderer2D::drawQuad({ 0.0f, 0.0f, -0.2f }, { 20.0f, 20.0f }, checkerboardTexture, { 1.0f, 1.0f, 1.0f, 1.0f }, 10.0f);

		Coffee::Renderer2D::drawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -rotation, { 0.8f, 0.2f, 0.3f, 1.0f });
		Coffee::Renderer2D::drawRotatedQuad({ 0.0f, 0.0f, -0.1f }, { 1.5f, 1.5f }, rotation, checkerboardTexture, { 0.2f, 0.8f, 0.3f, 1.0f }, 1.0f);

		for(float y = -(rows / 2.0f); y < rows / 2.0f; y += size) {
			for(float x = -(columns / 2.0f); x < columns / 2.0f; x += size) {
				const float red = (x + rows / 2.0f) / rows;
				const float blue = (y + columns / 2.0f) / columns;
				glm::vec4 color = { red, 0.45f, blue, 0.75f };

				Coffee::Renderer2D::drawQuad({ x, y, 0.1f }, { size - 0.05f, size - 0.05f }, color);
			}
		}
	}
	Coffee::Renderer2D::endScene();
	
}
void Sandbox2D::drawImgui() {
	CF_PROFILE_FUNCTION();
	
	ImGui::Begin("Renderer2D Stats");
	{
		const auto stats = Coffee::Renderer2D::getStats();
		ImGui::Text("Draw Calls: %d", stats.drawCalls);
		ImGui::Text("Quads: %d", stats.quadCount);
		ImGui::Text("Vertices: %d", stats.getTotalVertexCount());
		ImGui::Text("Indices: %d", stats.getTotalIndexCount());
		ImGui::Text("Textures: %d", stats.textureCount);
	}
	ImGui::End();

	ImGui::Begin("Settings");
	{
		int row = static_cast<int>(rows), col = static_cast<int>(columns);
		
		ImGui::SliderInt("Rows", &row, 1, 20);
		ImGui::SliderInt("Columns", &col, 1, 20);
		ImGui::SliderFloat("Size", &size, 0.1f, 1.0f);

		rows = static_cast<float>(row); columns = static_cast<float>(col);
	}
	ImGui::End();
}

void Sandbox2D::onEvent(Coffee::Event& e) {
	cameraController.onEvent(e);
}
