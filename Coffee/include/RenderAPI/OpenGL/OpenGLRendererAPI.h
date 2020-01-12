#pragma once

#include "Coffee/Renderer/RendererAPI.h"

namespace Coffee {

	class OpenGLRendererAPI : public RendererAPI {
	public:

		void init() override;

		void setViewport(unsigned x, unsigned y, unsigned width, unsigned height) override;

		void setClearColour(const glm::vec4& colour) override;
		void clearScreen() override;
		void drawIndexed(const Ref<VertexArray>& vertexArray) override;

	private:


		
	};
	
}
