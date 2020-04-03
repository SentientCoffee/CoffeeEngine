#include "CoffeePCH.h"
#include "Coffee/Renderer/Renderer2D.h"

#include "Coffee/Renderer/Shader.h"
#include "Coffee/Renderer/VertexArray.h"
#include "Coffee/Renderer/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Coffee;

ColouredQuad::ColouredQuad(const glm::vec3& position, const glm::vec2& dimensions, const glm::vec4& colour) :
	zIndexedPosition(position), dimensions(dimensions), colour(colour) {}

ColouredQuad::ColouredQuad(const glm::vec2& position, const glm::vec2& dimensions, const glm::vec4& colour) :
	position(position), zIndex(0.0f), dimensions(dimensions), colour(colour) {}

ColouredQuad::ColouredQuad(const glm::vec2& position, const float zIndex, const glm::vec2& dimensions, const glm::vec4& colour) :
	position(position), zIndex(zIndex), dimensions(dimensions), colour(colour) {}


TexturedQuad::TexturedQuad(const glm::vec3& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint, const float tilingFactor) :
	zIndexedPosition(position), dimensions(dimensions), texture(texture), tint(tint), tilingFactor(tilingFactor) {}

TexturedQuad::TexturedQuad(const glm::vec2& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint, const float tilingFactor) :
	position(position), zIndex(0.0f), dimensions(dimensions), texture(texture), tint(tint), tilingFactor(tilingFactor) {}

TexturedQuad::TexturedQuad(const glm::vec2& position, const float zIndex, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint, const float tilingFactor) :
	position(position), zIndex(zIndex), dimensions(dimensions), texture(texture), tint(tint), tilingFactor(tilingFactor) {}

struct QuadVertex {
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec4 colour;
};

struct Renderer2DData {

	const unsigned maxQuads = 10000;
	const unsigned maxVertices = maxQuads * 4;
	const unsigned maxIndices = maxQuads * 6;

	unsigned quadIndexCount = 0;

	QuadVertex* quadVboBase = nullptr;
	QuadVertex* quadVboPtr  = nullptr;

	Ref<VertexArray> quadVao;
	Ref<VertexBuffer> quadVbo;
	Ref<Shader> quadShader;
	Ref<Texture2D> whiteTexture;

};

static Renderer2DData storage;

void Renderer2D::init() {

	const auto quadIndices = new unsigned[storage.maxIndices];
	unsigned offset = 0;
	for(unsigned i = 0; i < storage.maxIndices; i += 6, offset += 4) {
		quadIndices[i + 0] = offset + 0;
		quadIndices[i + 1] = offset + 1;
		quadIndices[i + 2] = offset + 2;
		
		quadIndices[i + 3] = offset + 0;
		quadIndices[i + 4] = offset + 2;
		quadIndices[i + 5] = offset + 3;
	}
	
	storage.quadVboBase = new QuadVertex[storage.maxVertices];


	storage.quadVao = VertexArray::create();
	storage.quadVbo = VertexBuffer::create(storage.maxVertices * sizeof(QuadVertex));
	const Ref<IndexBuffer> quadIbo = IndexBuffer::create(quadIndices, storage.maxIndices);

	const BufferLayout quadLayout = {
		{ ShaderDataType::Vec3, "inPosition" },
		{ ShaderDataType::Vec2, "inUVs" },
		{ ShaderDataType::Vec4, "inColour" }
	};

	storage.quadVbo->setLayout(quadLayout);
	storage.quadVao->addVertexBuffer(storage.quadVbo);
	storage.quadVao->setIndexBuffer(quadIbo);
	
	storage.quadShader = Shader::create("assets/shaders/Texture.glsl");

	storage.quadShader->bind();
	storage.quadShader->setInt("uTextureAlbedo", 0);

	storage.whiteTexture = Texture2D::create(1, 1);
	unsigned whiteData = 0xFFFFFFFF;
	storage.whiteTexture->setData(&whiteData, sizeof(unsigned));

	delete[] quadIndices;
}

void Renderer2D::shutdown() {}

void Renderer2D::beginScene(const OrthographicCamera& camera) {
	
	storage.quadShader->bind();
	storage.quadShader->setMat4("uViewProjection", camera.getViewProjectionMatrix());

	storage.quadIndexCount = 0;
	storage.quadVboPtr = storage.quadVboBase;
}

void Renderer2D::endScene() {
	const unsigned dataSize = static_cast<unsigned>(reinterpret_cast<char*>(storage.quadVboPtr) - reinterpret_cast<char*>(storage.quadVboBase));
	storage.quadVbo->setData(storage.quadVboBase, dataSize);
	
	renderScene();
}

void Renderer2D::renderScene() {
	RenderCommand::drawIndexed(storage.quadVao, storage.quadIndexCount);
}

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& dimensions, const glm::vec4& colour) {
	drawQuad({ position.x, position.y, 0.0f }, dimensions, colour);
}
void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint) {
	drawQuad({ position.x, position.y, 0.0f }, dimensions, texture, tint);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& dimensions, const glm::vec4& colour) {
	storage.quadVboPtr->position = position;
	storage.quadVboPtr->colour = colour;
	storage.quadVboPtr->uv = { 0.0f, 0.0f };
	storage.quadVboPtr++;

	storage.quadVboPtr->position = { position.x + dimensions.x, position.y, position.z };
	storage.quadVboPtr->colour = colour;
	storage.quadVboPtr->uv = { 1.0f, 0.0f };
	storage.quadVboPtr++;

	storage.quadVboPtr->position = { position.x + dimensions.x, position.y + dimensions.y, position.z };
	storage.quadVboPtr->colour = colour;
	storage.quadVboPtr->uv = { 1.0f, 1.0f };
	storage.quadVboPtr++;

	storage.quadVboPtr->position = { position.x, position.y + dimensions.y, position.z };
	storage.quadVboPtr->colour = colour;
	storage.quadVboPtr->uv = { 0.0f, 1.0f };
	storage.quadVboPtr++;

	storage.quadIndexCount += 6;
	
	#if 0
	storage.whiteTexture->bind();
	
	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(dimensions.x, dimensions.y, 0.0f));
	storage.quadShader->setMat4("uModelMatrix", transform);
	storage.quadShader->setFloat("uTileFactor", 1.0f);

	storage.quadVao->bind();
	RenderCommand::drawIndexed(storage.quadVao);

	storage.whiteTexture->unbind();
	#endif

}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint) {
	texture->bind();

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(dimensions.x, dimensions.y, 0.0f));
	storage.quadShader->setMat4("uModelMatrix", transform);
	storage.quadShader->setVec4("uColour", tint);
	storage.quadShader->setFloat("uTileFactor", 1.0f);

	storage.quadVao->bind();
	RenderCommand::drawIndexed(storage.quadVao);
	texture->unbind();
}

void Renderer2D::drawQuad(const ColouredQuad& properties) {
	storage.whiteTexture->bind();

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), properties.zIndexedPosition) * glm::scale(glm::mat4(1.0f), glm::vec3(properties.dimensions.x, properties.dimensions.y, 0.0f));
	storage.quadShader->setMat4("uModelMatrix", transform);
	storage.quadShader->setVec4("uColour", properties.colour);
	storage.quadShader->setFloat("uTileFactor", 1.0f);

	storage.quadVao->bind();
	RenderCommand::drawIndexed(storage.quadVao);

	storage.whiteTexture->unbind();
}

void Renderer2D::drawQuad(const TexturedQuad& properties) {
	properties.texture->bind();

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), properties.zIndexedPosition) * glm::scale(glm::mat4(1.0f), glm::vec3(properties.dimensions.x, properties.dimensions.y, 0.0f));
	storage.quadShader->setMat4("uModelMatrix", transform);
	storage.quadShader->setVec4("uColour", properties.tint);
	storage.quadShader->setFloat("uTileFactor", properties.tilingFactor);

	storage.quadVao->bind();
	RenderCommand::drawIndexed(storage.quadVao);
	properties.texture->unbind();
}
