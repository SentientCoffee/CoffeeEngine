#pragma once

#include "Coffee/Renderer/VertexArray.h"

namespace Coffee {

	class OpenGLVertexArray : public VertexArray {
	public:

		OpenGLVertexArray();
		~OpenGLVertexArray();
		
		void bind() const override;
		void unbind() const override;
		void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override;
		const Ref<IndexBuffer>& getIndexBuffer() const override;

	private:
		
		unsigned int _rendererId;
		std::vector<Ref<VertexBuffer>> _vertexBuffers;
		Ref<IndexBuffer> _indexBuffer;
		
	};
	
}