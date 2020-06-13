#pragma once

#include "RendererAPI.h"

namespace Coffee {

	class RenderCommand {
	public:
		
		static void init();

		static void setClearColour(const glm::vec4& colour);
		static void setClearColour(float r, float g, float b, float a);
		static void clearScreen();

		static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

		static void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0);

	private:

		static RendererAPI* _rendererApi;
		
	};
	
}
