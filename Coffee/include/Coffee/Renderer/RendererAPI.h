#pragma once

#include "VertexArray.h"

#include <glm/glm.hpp>

namespace Coffee {

	class RendererAPI {
	public:

		virtual ~RendererAPI() = default;
		virtual void init() = 0;
		virtual void setViewport(unsigned x, unsigned y, unsigned width, unsigned height) = 0;

		enum class API : unsigned int {
			None = 0,
			OpenGL
		};

		virtual void setClearColour(const glm::vec4& colour) = 0;
		virtual void clearScreen() = 0;
		
		virtual void drawIndexed(const Ref<VertexArray>& vertexArray, unsigned indexCount) = 0;
		
		static API getAPI();

	private:

		static API _api;
		
	};
	
}
