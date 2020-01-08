#pragma once

#include "RenderCommand.h"

namespace Coffee {

	class Renderer {
	public:

		static void beginScene();
		static void endScene();
		
		static void submit(const std::shared_ptr<VertexArray>& vertexArray);

		static RendererAPI::API getAPI();
	};
}
