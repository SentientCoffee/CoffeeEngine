#pragma once

#include "Coffee/Renderer/Buffers.h"

namespace Coffee {

	class OpenGLVertexBuffer : public VertexBuffer {
	public:

		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer();

		void bind() const override;
		void unbind() const override;

		void setData(const void* data, uint32_t size) override;
		
		void setLayout(const BufferLayout& layout) override;
		const BufferLayout& getLayout() const override;
		
	private:

		uint32_t _rendererId;
		BufferLayout _layout = BufferLayout();
		
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:

		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer();

		void bind() const override;
		void unbind() const override;

		uint32_t getCount() const override;
		
	private:

		uint32_t _rendererId;
		uint32_t _indexCount;
		
	};
	
}