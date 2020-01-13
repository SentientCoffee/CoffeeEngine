#pragma once

#include "Coffee/Renderer/Texture.h"

#include <glad/glad.h>

namespace Coffee {

	class OpenGLTexture2D : public Texture2D {
	public:

		OpenGLTexture2D(unsigned width, unsigned height);
		OpenGLTexture2D(const std::string& filepath);
		~OpenGLTexture2D();
		
		void getWidth() const override;
		void getHeight() const override;
		
		void bind(unsigned slot = 0) const override;
		void unbind(unsigned slot = 0) const override;

		void setData(void* data, unsigned size) override;

	private:

		unsigned _rendererId = 0;
		unsigned _width, _height;
		std::string _texturePath;

		GLenum _internalFormat, _format;
	};
	 
}