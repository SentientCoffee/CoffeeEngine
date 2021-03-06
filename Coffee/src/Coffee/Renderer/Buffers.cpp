#include "CoffeePCH.h"
#include "Coffee/Renderer/Buffers.h"

#include "Coffee/Renderer/Renderer.h"
#include "RenderAPI/OpenGL/OpenGLBuffers.h"

using namespace Coffee;

// ----------------------------------------
// ----- Buffer layout element ------------
// ----------------------------------------

BufferElement::BufferElement(const ShaderDataType type, const std::string& name, const bool normalized) :
	name(name), type(type), size(shaderDataTypeSize(type)), offset(0), normalized(normalized) {}

uint32_t BufferElement::getComponentCount() const {
	switch(type) {
		case ShaderDataType::Bool:		return 1;
		case ShaderDataType::Int:		return 1;
		case ShaderDataType::Float:		return 1;

		case ShaderDataType::Vec2:		return 2;
		case ShaderDataType::Vec3:		return 3;
		case ShaderDataType::Vec4:		return 4;

		case ShaderDataType::IVec2:		return 2;
		case ShaderDataType::IVec3:		return 3;
		case ShaderDataType::IVec4:		return 4;

		case ShaderDataType::Mat3:		return 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4;
	}

	return 0;
}

// ----------------------------------------
// ----- Buffer layout --------------------
// ----------------------------------------

BufferLayout::BufferLayout(const std::vector<BufferElement>& elements) :
	_elements(elements) {
	strideOffsetCalc();
}

BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) :
	_elements(elements) {
	strideOffsetCalc();
}

std::vector<BufferElement> BufferLayout::getElements() const { return _elements; }
uint32_t BufferLayout::size() const { return static_cast<uint32_t>(_elements.size()); }
BufferLayout::BufferElemIterator BufferLayout::begin() { return _elements.begin(); }
BufferLayout::BufferElemIterator BufferLayout::end() { return _elements.end(); }
BufferLayout::ConstBufferElemIterator BufferLayout::begin() const { return _elements.begin(); }
BufferLayout::ConstBufferElemIterator BufferLayout::end() const { return _elements.end(); }

uint32_t BufferLayout::getStride() const { return _stride; }

void BufferLayout::strideOffsetCalc() {
	uint32_t offset = _stride = 0;
	
	for(auto& elem : _elements) {
		elem.offset = offset;
		offset += elem.size;
		_stride += elem.size;
	}
}

// ----------------------------------------
// ----- Vertex buffers -------------------
// ----------------------------------------

Ref<VertexBuffer> VertexBuffer::create(uint32_t size) {
	switch(Renderer::getAPI()) {
		case RendererAPI::API::None:		CF_CORE_ASSERT(false, "Coffee Engine does not support having no renderer API!"); return nullptr;
		case RendererAPI::API::OpenGL:		return createRef<OpenGLVertexBuffer>(size);
	}

	CF_CORE_ASSERT(false, "Unknown renderer API!");
	return nullptr;
}

Ref<VertexBuffer> VertexBuffer::create(std::vector<float>& vertices) {
	return create(vertices.data(), static_cast<uint32_t>(vertices.size() * sizeof(float)));
}

Ref<VertexBuffer> VertexBuffer::create(float* vertices, const uint32_t size) {
	switch(Renderer::getAPI()) {
		case RendererAPI::API::None:
			CF_CORE_ASSERT(false, "Coffee Engine does not support having no renderer API!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return createRef<OpenGLVertexBuffer>(vertices, size);
	}

	CF_CORE_ASSERT(false, "Unknown renderer API!");
	return nullptr;
}

// ----------------------------------------
// ----- Index buffers --------------------
// ----------------------------------------

Ref<IndexBuffer> IndexBuffer::create(std::vector<uint32_t>& indices) {
	return create(indices.data(), static_cast<uint32_t>(indices.size()));
}

Ref<IndexBuffer> IndexBuffer::create(uint32_t* indices, const uint32_t count) {
	switch(Renderer::getAPI()) {
		case RendererAPI::API::None:
			CF_CORE_ASSERT(false, "Coffee Engine does not support having no renderer API!");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, count);
	}

	CF_CORE_ASSERT(false, "Unknown renderer API!");
	return nullptr;
}
