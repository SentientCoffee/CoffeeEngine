#include "CoffeePCH.h"
#include "Coffee/Renderer/Texture.h"

#include "Coffee/Renderer/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLTexture.h"

using namespace Coffee;

Ref<Texture2D> Texture2D::create(const std::string& filepath) {
	switch(Renderer::getAPI()) {
		case RendererAPI::API::None:
			CF_CORE_ASSERT(false, "Coffee Engine does not support having no renderer API!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return createRef<OpenGLTexture2D>(filepath);
	}

	CF_CORE_ASSERT(false, "Unknown renderer API!");
	return nullptr;
}

Ref<Texture2D> Texture2D::create(const uint32_t width, const uint32_t height) {
	switch(Renderer::getAPI()) {
		case RendererAPI::API::None:		CF_CORE_ASSERT(false, "Coffee Engine does not support having no renderer API!"); return nullptr;
		case RendererAPI::API::OpenGL:		return createRef<OpenGLTexture2D>(width, height);
	}

	CF_CORE_ASSERT(false, "Unknown renderer API!");
	return nullptr;
}
