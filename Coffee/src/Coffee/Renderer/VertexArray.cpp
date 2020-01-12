#include "CoffeePCH.h"
#include "Coffee/Renderer/VertexArray.h"

#include "Coffee/Renderer/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLVertexArray.h"

using namespace Coffee;

Ref<VertexArray> VertexArray::create() {
	switch(Renderer::getAPI()) {
		case RendererAPI::API::None:
			CF_CORE_ASSERT(false, "Coffee Engine does not support having no renderer API!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
	}

	CF_CORE_ASSERT(false, "Unknown renderer API!");
	return nullptr;
}
