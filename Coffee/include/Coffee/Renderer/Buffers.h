#pragma once

#include "Coffee/Core/Core.h"

#include <vector>

namespace Coffee {

	enum class ShaderDataType : uint32_t {
		Bool = 0, Int, Float,
		Vec2, Vec3, Vec4,
		IVec2, IVec3, IVec4,
		Mat3, Mat4
		
	};

	static uint32_t shaderDataTypeSize(const ShaderDataType type) {
		switch(type) {
			case ShaderDataType::Bool:		return sizeof(bool);
			case ShaderDataType::Int:		return sizeof(int);
			case ShaderDataType::Float:		return sizeof(float);
			
			case ShaderDataType::Vec2:		return 2 * sizeof(float);
			case ShaderDataType::Vec3:		return 3 * sizeof(float);
			case ShaderDataType::Vec4:		return 4 * sizeof(float);
			
			case ShaderDataType::IVec2:		return 2 * sizeof(int);
			case ShaderDataType::IVec3:		return 3 * sizeof(int);
			case ShaderDataType::IVec4:		return 4 * sizeof(int);

			case ShaderDataType::Mat3:		return 3 * 3 * sizeof(float);
			case ShaderDataType::Mat4:		return 4 * 4 * sizeof(float);
		}

		CF_CORE_ASSERT(false, "Unknown shader data type!");
		return 0;
	}
	
	struct BufferElement {
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool normalized;

		BufferElement() = default;
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false);

		uint32_t getComponentCount() const;
	};

	class BufferLayout {

		using BufferElemVector = std::vector<BufferElement>;
		using BufferElemInitList = std::initializer_list<BufferElement>;
		using BufferElemIterator = std::vector<BufferElement>::iterator;
		using ConstBufferElemIterator = std::vector<BufferElement>::const_iterator;
		
	public:

		BufferLayout() = default;
		BufferLayout(const BufferElemVector& elements);
		BufferLayout(const BufferElemInitList& elements);
		
		BufferElemVector getElements() const;
		uint32_t size() const;
		BufferElemIterator begin();
		BufferElemIterator end();
		ConstBufferElemIterator begin() const;
		ConstBufferElemIterator end() const;

		uint32_t getStride() const;

	private:

		void strideOffsetCalc();

		BufferElemVector _elements;
		uint32_t _stride = 0;

	};
	
	class VertexBuffer {
	public:

		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& getLayout() const = 0;
		virtual void setData(const void* data, uint32_t size) = 0;

		static Ref<VertexBuffer> create(uint32_t size);
		static Ref<VertexBuffer> create(std::vector<float>& vertices);
		static Ref<VertexBuffer> create(float* vertices, uint32_t size);
		
	};


	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t getCount() const = 0;

		static Ref<IndexBuffer> create(std::vector<uint32_t>& indices);
		static Ref<IndexBuffer> create(uint32_t* indices, uint32_t count);
		
	};
}