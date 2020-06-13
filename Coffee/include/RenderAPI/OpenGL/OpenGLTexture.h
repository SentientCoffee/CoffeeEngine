#pragma once

#include "Coffee/Renderer/Texture.h"

#include <glad/glad.h>

namespace Coffee {

	class OpenGLTexture2D final : public Texture2D {
	public:

		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& filepath);
		~OpenGLTexture2D();

		bool operator==(const Texture2D& other) const override;
		
		uint32_t getWidth() const override;
		uint32_t getHeight() const override;
		
		void bind(uint32_t slot = 0) const override;
		void unbind(uint32_t slot = 0) const override;

		void setData(void* data, uint32_t size) override;

	private:

		uint32_t _rendererId = 0;
		uint32_t _width, _height;
		std::string _texturePath;

		GLenum _internalFormat, _format;
	};
	 
}