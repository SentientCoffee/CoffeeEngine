#pragma once

#include "RendererAPI.h"

namespace Coffee {

	class RenderCommand {
	public:

		static void setClearColour(const glm::vec4& colour);
		static void setClearColour(float r, float g, float b, float a);
		static void clearScreen();

		static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray);

	private:

		static RendererAPI* _rendererApi;
		
	};
	
}
