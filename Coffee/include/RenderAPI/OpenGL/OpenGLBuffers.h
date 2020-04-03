#pragma once

#include "Coffee/Renderer/Buffers.h"

namespace Coffee {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:

		OpenGLVertexBuffer(unsigned size);
		OpenGLVertexBuffer(float* vertices, unsigned int size);
		~OpenGLVertexBuffer();

		void bind() const override;
		void unbind() const override;

		void setData(const void* data, unsigned size) override;
		
		void setLayout(const BufferLayout& layout) override;
		const BufferLayout& getLayout() const override;
		
	private:

		unsigned _rendererId;
		BufferLayout _layout = BufferLayout();
		
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:

		OpenGLIndexBuffer(unsigned* indices, unsigned int count);
		~OpenGLIndexBuffer();

		void bind() const override;
		void unbind() const override;

		unsigned int getCount() const override;
		
	private:

		unsigned _rendererId;
		unsigned _indexCount;
		
	};
	
}