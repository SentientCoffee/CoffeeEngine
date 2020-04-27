#pragma once

#include "Coffee/Renderer/Camera.h"
#include "Coffee/Renderer/Shader.h"
#include "Coffee/Renderer/RenderCommand.h"

namespace Coffee {

	class Renderer {
	public:

		static void init();
		static void shutdown();
		static void onWindowResized(unsigned width, unsigned height);
		
		static void beginScene(OrthographicCamera& camera);
		static void endScene();
		
		static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static RendererAPI::API getAPI();
		static const Scope<ShaderLibrary>& getShaderLibrary();

	private:

		struct SceneData {
			glm::mat4 viewProjection;
		};

		static Scope<SceneData> sceneData;
		static Scope<ShaderLibrary> shaderLib;
		
	};
}
