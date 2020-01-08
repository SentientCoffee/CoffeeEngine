#pragma once

#include "Coffee/Renderer/VertexArray.h"

namespace Coffee {

	class OpenGLVertexArray : public VertexArray {
	public:

		OpenGLVertexArray();
		~OpenGLVertexArray();
		
		void bind() const override;
		void unbind() const override;
		void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override;
		const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override;

	private:
		
		unsigned int _rendererId;
		std::vector<std::shared_ptr<VertexBuffer>> _vertexBuffers;
		std::shared_ptr<IndexBuffer> _indexBuffer;
		
	};
	
}