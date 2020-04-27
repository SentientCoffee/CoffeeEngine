#include "CoffeePCH.h"
#include "Coffee/Renderer/Renderer.h"

#include "Coffee/Renderer/Renderer2D.h"

using namespace Coffee;

Scope<Renderer::SceneData> Renderer::sceneData = createScope<SceneData>();
Scope<ShaderLibrary> Renderer::shaderLib = createScope<ShaderLibrary>();

void Renderer::init() {
	CF_PROFILE_FUNCTION();
	RenderCommand::init();
	Renderer2D::init();
}

void Renderer::shutdown() {
	CF_PROFILE_FUNCTION();
	
	Renderer2D::shutdown();
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
