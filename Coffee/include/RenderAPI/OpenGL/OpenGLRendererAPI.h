#pragma once

#include "Coffee/Renderer/RendererAPI.h"

namespace Coffee {

	class OpenGLRendererAPI : public RendererAPI {
	public:

		void init() override;

		void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		void setClearColour(const glm::vec4& colour) override;
		void clearScreen() override;
		void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) override;
		
	};
	
}
