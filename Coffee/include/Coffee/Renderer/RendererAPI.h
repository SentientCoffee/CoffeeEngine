#pragma once

#include "VertexArray.h"

#include <glm/glm.hpp>

namespace Coffee {

	class RendererAPI {
	public:

		virtual ~RendererAPI() = default;

		enum class API : unsigned int {
			None = 0,
			OpenGL
		};

		virtual void setClearColour(const glm::vec4& colour) = 0;
		virtual void clearScreen() = 0;
		
		virtual void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		
		static API getAPI();

	private:

		static API _api;
		
	};
	
}