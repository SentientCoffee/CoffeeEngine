#pragma once

#include "Coffee/Renderer/Shader.h"

#include <glm/glm.hpp>

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

		void setBool(const std::string& name, bool value) override;
		void setInt(const std::string& name, int value) override;
		void setFloat(const std::string& name, float value) override;
		
		void setVec2(const std::string& name, const glm::vec2& value) override;
		void setVec3(const std::string& name, const glm::vec3& value) override;
		void setVec4(const std::string& name, const glm::vec4& value) override;
		
		void setMat3(const std::string& name, const glm::mat3& value) override;
		void setMat4(const std::string& name, const glm::mat4& value) override;

	private:
		
		void uploadUniform(const std::string& name, bool value) const;
		void uploadUniform(const std::string& name, int value) const;
		void uploadUniform(const std::string& name, float value) const;
		
		void uploadUniform(const std::string& name, const glm::vec2& value) const;
		void uploadUniform(const std::string& name, const glm::vec3& value) const;
		void uploadUniform(const std::string& name, const glm::vec4& value) const;
		
		void uploadUniform(const std::string& name, const glm::mat3& value) const;
		void uploadUniform(const std::string& name, const glm::mat4& value) const;

		static std::string readFile(const std::string& filepath);
		static std::unordered_map<ShaderType, std::string> processSource(const std::string& shaderSrc);

		static unsigned int createShader(const std::string& shaderSrc, ShaderType shaderType);
		void compileProgram(const std::unordered_map<ShaderType, std::string>& sources);

		unsigned int _rendererId = 0;
		std::string _name;

	};

}
