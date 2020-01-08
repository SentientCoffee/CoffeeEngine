#pragma once

#include "Coffee/Renderer/RendererAPI.h"

namespace Coffee {

	class OpenGLRendererAPI : public RendererAPI {
	public:
		
		void setClearColour(const glm::vec4& colour) override;
		void clearScreen() override;
		void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

	private:


		
	};
	
}
