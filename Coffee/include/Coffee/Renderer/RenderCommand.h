#pragma once

#include "RendererAPI.h"

namespace Coffee {

	class RenderCommand {
	public:
		
		static void init();

		static void setClearColour(const glm::vec4& colour);
		static void setClearColour(float r, float g, float b, float a);
		static void clearScreen();

		static void setViewport(unsigned x, unsigned y, unsigned width, unsigned height);

		static void drawIndexed(const Ref<VertexArray>& vertexArray, unsigned indexCount = 0);

	private:

		static RendererAPI* _rendererApi;
		
	};
	
}
