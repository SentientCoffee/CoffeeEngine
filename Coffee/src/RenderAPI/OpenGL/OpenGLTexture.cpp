#include "CoffeePCH.h"
#include "RenderAPI/OpenGL/OpenGLTexture.h"

#include <glad/glad.h>
#include <stb/stb_image.h>

using namespace Coffee;

OpenGLTexture2D::OpenGLTexture2D(const unsigned width, const unsigned height) :
	_width(width), _height(height)
{
	CF_PROFILE_FUNCTION();
	
	_internalFormat = GL_RGBA8;
	_format = GL_RGBA;

	CF_CORE_ASSERT(_internalFormat & _format, "Unsupported image format!");

	glCreateTextures(GL_TEXTURE_2D, 1, &_rendererId);
	glTextureStorage2D(_rendererId, 1, _internalFormat, _width, _height);

	glTextureParameteri(_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(_rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(_rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(_rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath) :
	_texturePath(filepath)
{
	CF_PROFILE_FUNCTION();

	int width = 0, height = 0, channels = 0;
	stbi_set_flip_vertically_on_load(true);
	stbi_uc* data = nullptr;
	{
		CF_PROFILE_SCOPE("[stbi_load] - OpenGLTexture2D::OpenGLTexture2D(const std::string&)");
		data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
	}

	if(data == nullptr) {
		CF_CORE_ASSERT(data, "Failed to load image!\n\tTexture path: {0}", filepath);
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
	_internalFormat = internalFormat;
	_format = format;
	
	glCreateTextures(GL_TEXTURE_2D, 1, &_rendererId);
	glTextureStorage2D(_rendererId, 1, _internalFormat, _width, _height);

	glTextureParameteri(_rendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(_rendererId, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTextureParameteri(_rendererId, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(_rendererId, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(_rendererId, 0, 0, 0, _width, _height, _format, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D() {
	CF_PROFILE_FUNCTION();
	glDeleteTextures(1, &_rendererId);
}

bool OpenGLTexture2D::operator==(const Texture& other) const { return ((OpenGLTexture2D&)other)._rendererId; }

unsigned OpenGLTexture2D::getWidth() const { return _width; }
unsigned OpenGLTexture2D::getHeight() const { return _height; }

void OpenGLTexture2D::bind(const unsigned slot) const {
	CF_PROFILE_FUNCTION();
	glBindTextureUnit(slot, _rendererId);
}
void OpenGLTexture2D::unbind(const unsigned slot) const {
	CF_PROFILE_FUNCTION();
	glBindTextureUnit(slot, 0);
}

void OpenGLTexture2D::setData(void* data, const unsigned size) {
	CF_PROFILE_FUNCTION();
	const unsigned bpp = _format == GL_RGBA ? 4 : 3;
	CF_CORE_ASSERT(size == _width * _height * bpp, "Data must be entire texture!");
	glTextureSubImage2D(_rendererId, 0, 0, 0, _width, _height, _format, GL_UNSIGNED_BYTE, data);
}
