#pragma once

#include "Coffee/Renderer/Texture.h"

#include <glad/glad.h>

namespace Coffee {

	class OpenGLTexture2D : public Texture2D {
	public:

		OpenGLTexture2D(unsigned width, unsigned height);
		OpenGLTexture2D(const std::string& filepath);
		~OpenGLTexture2D();

		bool operator==(const Texture& other) const override;
		
		unsigned getWidth() const override;
		unsigned getHeight() const override;
		
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