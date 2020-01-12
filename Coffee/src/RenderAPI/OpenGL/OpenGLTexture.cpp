#include "CoffeePCH.h"
#include "RenderAPI/OpenGL/OpenGLTexture.h"

#include <glad/glad.h>
#include <stb/stb_image.h>

using namespace Coffee;

OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath) :
	_texturePath(filepath) {
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

	if(data == nullptr) {
		CF_CORE_ERROR("Texture path: {0}", filepath);
		CF_CORE_ASSERT(data, "Failed to load image!");
	}

	_width = width; _height = height;

	GLenum internalFormat = 0, format = 0;
	if(channels == 4) {
		internalFormat = GL_RGBA8;
		format = GL_RGBA;
	}
	else if(channels == 3) {
		internalFormat = GL_RGB8;
		format = GL_RGB;
	}

	CF_CORE_ASSERT(internalFormat & format, "Unsupported image format!");
	
	glCreateTextures(GL_TEXTURE_2D, 1, &_rendererId);
	glTextureStorage2D(_rendererId, 1, internalFormat, _width, _height);

	glTextureParameteri(_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(_rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureSubImage2D(_rendererId, 0, 0, 0, _width, _height, format, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D() {
	glDeleteTextures(1, &_rendererId);
}

void OpenGLTexture2D::getWidth() const {}
void OpenGLTexture2D::getHeight() const {}
void OpenGLTexture2D::bind(const unsigned slot) const {
	glBindTextureUnit(slot, _rendererId);
}
void OpenGLTexture2D::unbind(const unsigned slot) const {
	glBindTextureUnit(slot, 0);
}
