#pragma once

#include "Coffee/Renderer/Shader.h"

#include <glm/glm.hpp>

#include <optional>

namespace Coffee {

	enum class ShaderType : unsigned int {
		None = 0,
		Vertex,
		Fragment,
		Geometry
	};

	class OpenGLShader : public Shader {
	public:

		OpenGLShader() = default;
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		void bind() const override;
		void unbind() const override;

		const std::string& getName() const override;

		void setUniform(const std::string& name, bool value) const;
		void setUniform(const std::string& name, int value) const;
		void setUniform(const std::string& name, float value) const;
		
		void setUniform(const std::string& name, const glm::vec2& value) const;
		void setUniform(const std::string& name, const glm::vec3& value) const;
		void setUniform(const std::string& name, const glm::vec4& value) const;
		
		void setUniform(const std::string& name, const glm::mat3& value) const;
		void setUniform(const std::string& name, const glm::mat4& value) const;

	private:

		static std::string readFile(const std::string& filepath);
		static std::unordered_map<ShaderType, std::string> processSource(const std::string& shaderSrc);

		unsigned int createShader(const std::string& shaderSrc, ShaderType shaderType);
		void compileProgram(const std::unordered_map<ShaderType, std::string>& sources);

		unsigned int _rendererId = 0;
		std::string _name;

	};

}
