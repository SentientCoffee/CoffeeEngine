#include "CoffeePCH.h"
#include "Coffee/Renderer/Shader.h"

#include <glad/glad.h>

using namespace Coffee;

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
	CF_CORE_ASSERT(!vertexSrc.empty(), "Vertex shader could not be read!");
	CF_CORE_ASSERT(!fragmentSrc.empty(), "Fragment shader could not be read!");

	const unsigned int vertShader = createShader(vertexSrc, ShaderType::Vertex);
	const unsigned int fragShader = createShader(fragmentSrc, ShaderType::Fragment);
	
	_rendererId = glCreateProgram();
	compileProgram(vertShader, fragShader);
}

Shader::~Shader() { glDeleteProgram(_rendererId); }

unsigned Shader::createShader(const std::string& shaderSrc, const ShaderType shaderType) {
	unsigned int shaderHandle = 0;
	
	switch(shaderType) {
		case ShaderType::Vertex:
			shaderHandle = glCreateShader(GL_VERTEX_SHADER);
			break;
		case ShaderType::Fragment:
			shaderHandle = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		case ShaderType::Geometry:
			shaderHandle = glCreateShader(GL_GEOMETRY_SHADER);
			break;
	}

	auto shaderSource = shaderSrc.c_str();
	glShaderSource(shaderHandle, 1, &shaderSource, nullptr);
	glCompileShader(shaderHandle);

	int success;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
	if(!success) {
		int logLength;
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> infoLog(logLength);
		glGetShaderInfoLog(shaderHandle, logLength, &logLength, infoLog.data());
		glDeleteShader(shaderHandle);
		
		std::string type;
		switch(shaderType) {
			case ShaderType::Vertex:
				type = "Vertex";
				break;
			case ShaderType::Fragment:
				type = "Fragment";
				break;
			case ShaderType::Geometry:
				type = "Geometry";
				break;
		}

		CF_CORE_CRITICAL("{0} shader:", type);
		CF_CORE_CRITICAL("{0}", infoLog.data());
		CF_CORE_ASSERT(success, "Failed to compile shader!");
		return 0;
	}

	return shaderHandle;
}

void Shader::compileProgram(const unsigned int vertShader, const unsigned int fragShader, std::optional<unsigned> geomShader) {
	CF_CORE_ASSERT(vertShader, "No vertex shader linked!");
	CF_CORE_ASSERT(fragShader, "No fragment shader linked!");

	glAttachShader(_rendererId, vertShader);
	glAttachShader(_rendererId, fragShader);
	
	if(geomShader) {
		CF_CORE_ASSERT(!geomShader.value(), "No geometry shader linked!");
		glAttachShader(_rendererId, geomShader.value());
	}

	glLinkProgram(_rendererId);
	
	int success;
	glGetProgramiv(_rendererId, GL_LINK_STATUS, &success);
	if(!success) {
		int logLength;
		glGetProgramiv(_rendererId, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> infoLog(logLength);
		glGetProgramInfoLog(_rendererId, logLength, &logLength, infoLog.data());

		glDeleteProgram(_rendererId);
		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
		if(geomShader) {
			glDeleteShader(geomShader.value());
		}

		CF_CORE_ASSERT(success, "Failed to link shader program!\n{0}", infoLog.data());
	}

	glDetachShader(_rendererId, vertShader);
	glDetachShader(_rendererId, fragShader);
	if(geomShader) {
		glDetachShader(_rendererId, geomShader.value());
	}
}


void Shader::bind() const { glUseProgram(_rendererId); }
void Shader::unbind() { glUseProgram(0); }