#pragma once

namespace Coffee {

	enum class RendererAPI : unsigned int {
		None = 0,
		OpenGL
	};


	class Renderer {
	public:

		static RendererAPI getAPI();
		
	private:

		static RendererAPI _api;
		
	};
}