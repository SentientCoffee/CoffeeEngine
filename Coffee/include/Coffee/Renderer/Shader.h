#pragma once

#include <optional>
#include <string>

namespace Coffee {

	enum class ShaderType : unsigned int {
		Vertex = 0,
		Fragment,
		Geometry
	};
	
	class Shader {
	public:

		Shader() = default;
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void bind() const;
		static void unbind();

	private:

		unsigned int createShader(const std::string& shaderSrc, ShaderType shaderType);
		void compileProgram(unsigned int vertShader, unsigned int fragShader, std::optional<unsigned> geomShader = std::nullopt);

		unsigned int _rendererId;
		
	};
	
}