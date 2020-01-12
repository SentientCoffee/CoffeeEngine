#pragma once

#include "Coffee/Renderer/Texture.h"

namespace Coffee {

	class OpenGLTexture2D : public Texture2D {
	public:

		OpenGLTexture2D(const std::string& filepath);
		~OpenGLTexture2D();
		
		void getWidth() const override;
		void getHeight() const override;
		void bind(unsigned slot = 0) const override;
		void unbind(unsigned slot = 0) const override;
		
	private:

		unsigned _rendererId = 0;
		unsigned _width, _height;
		std::string _texturePath;
	};
	 
}