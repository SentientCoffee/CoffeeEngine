#include "CoffeePCH.h"
#include "Coffee/Renderer/Renderer.h"

#include "RenderAPI/OpenGL/OpenGLShader.h"

using namespace Coffee;

Renderer::SceneData* Renderer::sceneData = new SceneData;
ShaderLibrary* Renderer::shaderLib = new ShaderLibrary;

void Renderer::init() {
	RenderCommand::init();
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
	std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniform("uViewProjection", sceneData->viewProjection);
	std::dynamic_pointer_cast<OpenGLShader>(shader)->setUniform("uModelMatrix", transform);
	
	vertexArray->bind();
	RenderCommand::drawIndexed(vertexArray);
}

RendererAPI::API Renderer::getAPI() { return RendererAPI::getAPI(); }
ShaderLibrary* Renderer::getShaderLibrary() { return shaderLib; }
