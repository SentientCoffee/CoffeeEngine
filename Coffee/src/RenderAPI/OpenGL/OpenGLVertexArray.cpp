#include "CoffeePCH.h"
#include "RenderAPI/OpenGL/OpenGLVertexArray.h"

#include "Coffee/Renderer/Buffers.h"

#include <glad/glad.h>

using namespace Coffee;

static GLenum shaderDataTypeToOpenGLBaseType(const ShaderDataType type) {
	switch(type) {
		case ShaderDataType::Bool:		return GL_BOOL;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Float:		return GL_FLOAT;

		case ShaderDataType::Vec2:		return GL_FLOAT;
		case ShaderDataType::Vec3:		return GL_FLOAT;
		case ShaderDataType::Vec4:		return GL_FLOAT;

		case ShaderDataType::IVec2:		return GL_INT;
		case ShaderDataType::IVec3:		return GL_INT;
		case ShaderDataType::IVec4:		return GL_INT;

		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
	}

	CF_CORE_ASSERT(false, "Unknown shader data type!");
	return 0;
}

OpenGLVertexArray::OpenGLVertexArray() :
	_rendererId(0), _indexBuffer(nullptr)
{
	CF_PROFILE_FUNCTION();
	glCreateVertexArrays(1, &_rendererId);
}

OpenGLVertexArray::~OpenGLVertexArray() {
	CF_PROFILE_FUNCTION();
	glDeleteVertexArrays(1, &_rendererId);
}

void OpenGLVertexArray::bind() const { CF_PROFILE_FUNCTION(); glBindVertexArray(_rendererId); }
void OpenGLVertexArray::unbind() const { CF_PROFILE_FUNCTION(); glBindVertexArray(0); }

void OpenGLVertexArray::addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) {
	CF_PROFILE_FUNCTION();
	
	CF_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(), "Vertex buffer has no layout!");
	
	glBindVertexArray(_rendererId);
	vertexBuffer->bind();
	
	uint32_t i = 0;
	for(const auto& elem : vertexBuffer->getLayout()) {
		glEnableVertexAttribArray(i);

		glVertexAttribPointer(i, elem.getComponentCount(),
			shaderDataTypeToOpenGLBaseType(elem.type),
			elem.normalized ? GL_TRUE : GL_FALSE,
			vertexBuffer->getLayout().getStride(),
			reinterpret_cast<const void*>(static_cast<__int64>(elem.offset)));

		++i;
	}
	
	_vertexBuffers.push_back(vertexBuffer);
}

void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) {
	CF_PROFILE_FUNCTION();
	
	glBindVertexArray(_rendererId);
	indexBuffer->bind();
	
	_indexBuffer = indexBuffer;
}

const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::getVertexBuffers() const { return _vertexBuffers; }
const Ref<IndexBuffer>& OpenGLVertexArray::getIndexBuffer() const { return _indexBuffer; }
