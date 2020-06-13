#include "CoffeePCH.h"
#include "RenderAPI/OpenGL/OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

using namespace Coffee;

static ShaderType shaderTypeFromString(const std::string& type) {
	if(type == "vertex")							return ShaderType::Vertex;
	if(type == "fragment" || type == "pixel")		return ShaderType::Fragment;
	if(type == "geometry")							return ShaderType::Geometry;

	CF_CORE_ASSERT(false, "Unknown shader type!");
	return ShaderType::None;
}

OpenGLShader::OpenGLShader(const std::string& filepath) {
	CF_PROFILE_FUNCTION();
	
	const std::string shaderSrc = readFile(filepath);
	const std::unordered_map<ShaderType, std::string> sources = processSource(shaderSrc);
	compileProgram(sources);

	// Extract name from filepath
	auto lastSlash = filepath.find_last_of("/\\");
	lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
	const auto lastDot = filepath.rfind('.');
	const auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
	_name = filepath.substr(lastSlash, count);
}

OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) :
	_name(name)
{
	CF_PROFILE_FUNCTION();
	
	CF_CORE_ASSERT(!vertexSrc.empty(), "Vertex shader could not be read!");
	CF_CORE_ASSERT(!fragmentSrc.empty(), "Fragment shader could not be read!");
	
	std::unordered_map<ShaderType, std::string> sources = {};
	sources[ShaderType::Vertex] = vertexSrc;
	sources[ShaderType::Fragment] = fragmentSrc;

	compileProgram(sources);
}

OpenGLShader::~OpenGLShader() {
	CF_PROFILE_FUNCTION();
	glDeleteProgram(_rendererId);
}

std::string OpenGLShader::readFile(const std::string& filepath) {
	CF_PROFILE_FUNCTION();
	
	std::string result;
	std::ifstream in(filepath, std::ios::in | std::ios::binary);

	if(in.good()) {
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	else {
		CF_CORE_ERROR("Shader file {0} could not be opened!", filepath);
	}

	return result;
}

std::unordered_map<ShaderType, std::string> OpenGLShader::processSource(const std::string& shaderSrc) {
	CF_PROFILE_FUNCTION();
	
	std::unordered_map<ShaderType, std::string> shaderSources = {};

	const char* typeToken = "#type";
	const size_t typeTokenLength = strlen(typeToken);
	size_t pos = shaderSrc.find(typeToken, 0);

	while(pos != std::string::npos) {
		const size_t eol = shaderSrc.find_first_of("\r\n", pos);
		CF_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
		const size_t begin = pos + typeTokenLength + 1;
		std::string type = shaderSrc.substr(begin, eol - begin);
		CF_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel" || type == "geometry", "Invalid shader type specified!");

		const size_t nextLinePos = shaderSrc.find_first_not_of("\r\n", eol);
		pos = shaderSrc.find(typeToken, nextLinePos);
		shaderSources[shaderTypeFromString(type)] = shaderSrc.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? shaderSrc.size() - 1 : nextLinePos));
	}

	return shaderSources;
}

uint32_t OpenGLShader::createShader(const std::string& shaderSrc, const ShaderType shaderType) {
	CF_PROFILE_FUNCTION();
	
	uint32_t shaderHandle = 0;

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
		default: break;
	}

	const char* shaderSource = shaderSrc.c_str();
	glShaderSource(shaderHandle, 1, &shaderSource, nullptr);
	glCompileShader(shaderHandle);

	int success = 0;
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &success);
	if(!success) {
		int logLength = 0;
		glGetShaderiv(shaderHandle, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> infoLog;
		infoLog.reserve(logLength);
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
			default: break;
		}

		CF_CORE_ASSERT(success, "Failed to compile {0} shader!\n\t{1}", type, infoLog.data());
		return 0;
	}

	return shaderHandle;
}

void OpenGLShader::compileProgram(const std::unordered_map<ShaderType, std::string>& sources) {
	CF_PROFILE_FUNCTION();
	
	const uint32_t program = glCreateProgram();
	CF_CORE_ASSERT(sources.size() <= 3, "Only up to 3 shaders are supported!");
	std::array<uint32_t, 3> shaderIds {};

	int shaderIdIndex = 0;
	for(const auto& src : sources) {
		const uint32_t shader = createShader(src.second, src.first);
		glAttachShader(program, shader);
		shaderIds[shaderIdIndex++] = shader;
	}

	glLinkProgram(program);

	int success = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if(!success) {
		int logLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> infoLog;
		infoLog.reserve(logLength);
		glGetProgramInfoLog(program, logLength, &logLength, infoLog.data());

		glDeleteProgram(program);

		for(auto& id : shaderIds) {
			glDeleteShader(id);
		}

		CF_CORE_ASSERT(success, "Failed to link shader program!\n\t{0}", infoLog.data());
	}

	for(auto& id : shaderIds) {
		glDetachShader(program, id);
	}

	_rendererId = program;
}

void OpenGLShader::bind() const { CF_PROFILE_FUNCTION(); glUseProgram(_rendererId); }
void OpenGLShader::unbind() const { CF_PROFILE_FUNCTION(); glUseProgram(0); }

const std::string& OpenGLShader::getName() const { return _name; }

void OpenGLShader::setBool(const std::string& name, const bool value) {
	CF_PROFILE_FUNCTION();
	uploadUniform(name, value);
}
void OpenGLShader::setInt(const std::string& name, const int value) {
	CF_PROFILE_FUNCTION();
	uploadUniform(name, value);
}
void OpenGLShader::setFloat(const std::string& name, const float value) {
	CF_PROFILE_FUNCTION();
	uploadUniform(name, value);
}
void OpenGLShader::setVec2(const std::string& name, const glm::vec2& value) {
	CF_PROFILE_FUNCTION();
	uploadUniform(name, value);
}
void OpenGLShader::setVec3(const std::string& name, const glm::vec3& value) {
	CF_PROFILE_FUNCTION();
	uploadUniform(name, value);
}
void OpenGLShader::setVec4(const std::string& name, const glm::vec4& value) {
	CF_PROFILE_FUNCTION();
	uploadUniform(name, value);
}
void OpenGLShader::setMat3(const std::string& name, const glm::mat3& value) {
	CF_PROFILE_FUNCTION();
	uploadUniform(name, value);
}
void OpenGLShader::setMat4(const std::string& name, const glm::mat4& value) {
	CF_PROFILE_FUNCTION();
	uploadUniform(name, value);
}

void OpenGLShader::setIntArray(const std::string& name, int* values, const uint32_t count) {
	CF_PROFILE_FUNCTION();
	uploadUniformArray(name, values, count);
}

int OpenGLShader::getUniformLocation(const std::string& uniformName) const {
	const int location = glGetUniformLocation(_rendererId, uniformName.c_str());

	if(location == -1) {
		CF_CORE_WARNING("Could not find uniform {0}!", uniformName);
		CF_CORE_WARNING("\tShader: {0}", _name);
	}

	return location;
}

void OpenGLShader::uploadUniform(const std::string& name, const bool value) const  { glUniform1i(getUniformLocation(name), static_cast<int>(value)); }
void OpenGLShader::uploadUniform(const std::string& name, const int value) const   { glUniform1i(getUniformLocation(name), value); }
void OpenGLShader::uploadUniform(const std::string& name, const float value) const { glUniform1f(getUniformLocation(name), value); }

void OpenGLShader::uploadUniform(const std::string& name, const glm::vec2& value) const { glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value)); }
void OpenGLShader::uploadUniform(const std::string& name, const glm::vec3& value) const { glUniform3fv(getUniformLocation(name), 1, glm::value_ptr(value)); }
void OpenGLShader::uploadUniform(const std::string& name, const glm::vec4& value) const { glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value)); }

void OpenGLShader::uploadUniform(const std::string& name, const glm::mat3& value) const { glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }
void OpenGLShader::uploadUniform(const std::string& name, const glm::mat4& value) const { glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value)); }

void OpenGLShader::uploadUniformArray(const std::string& name, int* values, const uint32_t count) const { glUniform1iv(getUniformLocation(name), count, values); }
