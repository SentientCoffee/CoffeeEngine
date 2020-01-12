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
			return std::make_shared<OpenGLTexture2D>(filepath);
	}

	CF_CORE_ASSERT(false, "Unknown renderer API!");
	return nullptr;
}
