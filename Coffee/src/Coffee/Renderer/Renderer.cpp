#include "CoffeePCH.h"
#include "Coffee/Renderer/Renderer.h"

using namespace Coffee;

void Renderer::beginScene() {}
void Renderer::endScene() {}

void Renderer::submit(const std::shared_ptr<VertexArray>& vertexArray) {
	vertexArray->bind();
	RenderCommand::drawIndexed(vertexArray);
}

RendererAPI::API Renderer::getAPI() { return RendererAPI::getAPI(); }
