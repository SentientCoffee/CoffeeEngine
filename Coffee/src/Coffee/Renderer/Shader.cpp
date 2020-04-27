#include "CoffeePCH.h"
#include "Coffee/Renderer/Shader.h"

#include "Coffee/Renderer/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLShader.h"

using namespace Coffee;

// ----------------------------------------------------------------------
// ----- Shader ---------------------------------------------------------
// ----------------------------------------------------------------------

Ref<Shader> Shader::create(const std::string& filepath) {
	switch(Renderer::getAPI()) {
		case RendererAPI::API::None:		CF_CORE_ASSERT(false, "Coffee Engine does not support having no renderer API!"); return nullptr;
		case RendererAPI::API::OpenGL:		return createRef<OpenGLShader>(filepath);
	}

	CF_CORE_ASSERT(false, "Unknown renderer API!");
	return nullptr;
}

Ref<Shader> Shader::create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
	switch(Renderer::getAPI()) {
		case RendererAPI::API::None:		CF_CORE_ASSERT(false, "Coffee Engine does not support having no renderer API!"); return nullptr;
		case RendererAPI::API::OpenGL:		return createRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
	}

	CF_CORE_ASSERT(false, "Unknown renderer API!");
	return nullptr;
}

// ----------------------------------------------------------------------
// ----- Shader library -------------------------------------------------
// ----------------------------------------------------------------------

void ShaderLibrary::add(const Ref<Shader>& shader) {
	const auto& name = shader->getName();
	add(name, shader);
}

void ShaderLibrary::add(const std::string& name, const Ref<Shader>& shader) {
	CF_CORE_ASSERT(!hasShader(name), "Shader already exists!");
	_shaders[name] = shader;
}

Ref<Shader> ShaderLibrary::load(const std::string& filepath) {
	auto shader = Shader::create(filepath);
	add(shader);
	return shader;
}
Ref<Shader> ShaderLibrary::load(const std::string& name, const std::string& filepath) {
	auto shader = Shader::create(filepath);
	add(name, shader);
	return shader;
}
Ref<Shader> ShaderLibrary::get(const std::string& name) {
	CF_CORE_ASSERT(hasShader(name), "Shader not found!");
	return _shaders[name];
}

bool ShaderLibrary::hasShader(const std::string& name) const { return _shaders.find(name) != _shaders.end(); }

