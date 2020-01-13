#include "CoffeePCH.h"
#include "Coffee/Renderer/Renderer.h"

#include "Coffee/Renderer/Renderer2D.h"

using namespace Coffee;

Scope<Renderer::SceneData> Renderer::sceneData = std::make_unique<SceneData>();
Scope<ShaderLibrary> Renderer::shaderLib = std::make_unique<ShaderLibrary>();

void Renderer::init() {
	RenderCommand::init();
	Renderer2D::init();
}

void Renderer::onWindowResized(const unsigned width, const unsigned height) {
	RenderCommand::setViewport(0, 0, width, height);
}

void Renderer::beginScene(OrthographicCamera& camera) {
	sceneData->viewProjection = camera.getViewProjectionMatrix();
}
void Renderer::endScene() {}

void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
	shader->bind();
	shader->setMat4("uViewProjection", sceneData->viewProjection);
	shader->setMat4("uModelMatrix", transform);
	
	vertexArray->bind();
	RenderCommand::drawIndexed(vertexArray);
}

RendererAPI::API Renderer::getAPI() { return RendererAPI::getAPI(); }
const Scope<ShaderLibrary>& Renderer::getShaderLibrary() { return shaderLib; }
