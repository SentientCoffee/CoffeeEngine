#pragma once

#include "VertexArray.h"

#include <glm/glm.hpp>

namespace Coffee {

	class RendererAPI {
	public:

		virtual ~RendererAPI() = default;
		virtual void init() = 0;
		virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		enum class API : uint32_t {
			None = 0,
			OpenGL
		};

		virtual void setClearColour(const glm::vec4& colour) = 0;
		virtual void clearScreen() = 0;
		
		virtual void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount) = 0;
		
		static API getAPI();

	private:

		static API _api;
		
	};
	
}
