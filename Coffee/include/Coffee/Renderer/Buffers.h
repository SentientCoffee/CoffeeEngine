#pragma once

#include <vector>

namespace Coffee {

	enum class ShaderDataType : unsigned int {
		Bool = 0, Int, Float,
		Vec2, Vec3, Vec4,
		IVec2, IVec3, IVec4,
		Mat3, Mat4
		
	};

	static unsigned int shaderDataTypeSize(const ShaderDataType type) {
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
		unsigned size;
		unsigned offset;
		bool normalized;

		BufferElement() = default;
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false);

		unsigned int getComponentCount() const;
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
		unsigned int size() const;
		BufferElemIterator begin();
		BufferElemIterator end();
		ConstBufferElemIterator begin() const;
		ConstBufferElemIterator end() const;

		unsigned int getStride() const;

	private:

		void strideOffsetCalc();

		BufferElemVector _elements;
		unsigned int _stride;

	};
	
	class VertexBuffer {
	public:

		virtual ~VertexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void setLayout(const BufferLayout& layout) = 0;
		virtual const BufferLayout& getLayout() const = 0;

		static VertexBuffer* create(std::vector<float>& vertices);
		static VertexBuffer* create(float* vertices, unsigned int size);
		
	};


	class IndexBuffer {
	public:
		virtual ~IndexBuffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual unsigned int getCount() const = 0;

		static IndexBuffer* create(std::vector<unsigned>& indices);
		static IndexBuffer* create(unsigned* indices, unsigned int count);
		
	};
}