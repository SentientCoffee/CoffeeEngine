#include "CoffeePCH.h"
#include "Coffee/Renderer/GraphicsContext.h"

#include "Coffee/Renderer/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLContext.h"

using namespace Coffee;

Scope<GraphicsContext> GraphicsContext::create(void* window) {
	switch(Renderer::getAPI()) {
		case RendererAPI::API::None:		CF_CORE_ASSERT(false, "RendererAPI::None is not currently supported!"); return nullptr;
		case RendererAPI::API::OpenGL:		return createScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
	}

	CF_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}
