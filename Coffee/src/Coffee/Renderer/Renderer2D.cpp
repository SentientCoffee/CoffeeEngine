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

struct Renderer2DStorage {

	Ref<VertexArray> quadVao;
	Ref<Shader> quadShader;
	Ref<Texture2D> whiteTexture;

};

static Renderer2DStorage* storage;

void Renderer2D::init() {

	storage = new Renderer2DStorage();
	
	std::vector<float> squareVertices = {
		// Position				// UV coords
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
	};

	std::vector<unsigned> squareIndices = {
		0, 1, 2,
		0, 2, 3
	};

	storage->quadVao = VertexArray::create();
	Ref<VertexBuffer> squareVbo = VertexBuffer::create(squareVertices);
	Ref<IndexBuffer> squareIbo = IndexBuffer::create(squareIndices);

	const BufferLayout squareLayout = {
		{ ShaderDataType::Vec3, "inPosition" },
		{ ShaderDataType::Vec2, "inUVs" }
	};

	squareVbo->setLayout(squareLayout);
	storage->quadVao->addVertexBuffer(squareVbo);
	storage->quadVao->setIndexBuffer(squareIbo);

	storage->quadShader = Shader::create("assets/shaders/Texture.glsl");

	storage->quadShader->bind();
	storage->quadShader->setInt("uTextureAlbedo", 0);

	storage->whiteTexture = Texture2D::create(1, 1);
	unsigned whiteData = 0xFFFFFFFF;
	storage->whiteTexture->setData(&whiteData, sizeof(unsigned));
}

void Renderer2D::shutdown() {
	delete storage;
}

void Renderer2D::beginScene(const OrthographicCamera& camera) {
	storage->quadShader->bind();
	storage->quadShader->setMat4("uViewProjection", camera.getViewProjectionMatrix());
}

void Renderer2D::endScene() {}

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& dimensions, const glm::vec4& colour) {
	drawQuad({ position.x, position.y, 0.0f }, dimensions, colour);
}
void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint) {
	drawQuad({ position.x, position.y, 0.0f }, dimensions, texture, tint);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& dimensions, const glm::vec4& colour) {
	storage->whiteTexture->bind();
	
	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(dimensions.x, dimensions.y, 0.0f));
	storage->quadShader->setMat4("uModelMatrix", transform);
	storage->quadShader->setVec4("uColour", colour);
	storage->quadShader->setFloat("uTileFactor", 1.0f);

	storage->quadVao->bind();
	RenderCommand::drawIndexed(storage->quadVao);

	storage->whiteTexture->unbind();
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint) {
	texture->bind();

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), glm::vec3(dimensions.x, dimensions.y, 0.0f));
	storage->quadShader->setMat4("uModelMatrix", transform);
	storage->quadShader->setVec4("uColour", tint);
	storage->quadShader->setFloat("uTileFactor", 1.0f);

	storage->quadVao->bind();
	RenderCommand::drawIndexed(storage->quadVao);
	texture->unbind();
}

void Renderer2D::drawQuad(const ColouredQuad& properties) {
	storage->whiteTexture->bind();

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), properties.zIndexedPosition) * glm::scale(glm::mat4(1.0f), glm::vec3(properties.dimensions.x, properties.dimensions.y, 0.0f));
	storage->quadShader->setMat4("uModelMatrix", transform);
	storage->quadShader->setVec4("uColour", properties.colour);
	storage->quadShader->setFloat("uTileFactor", 1.0f);

	storage->quadVao->bind();
	RenderCommand::drawIndexed(storage->quadVao);

	storage->whiteTexture->unbind();
}

void Renderer2D::drawQuad(const TexturedQuad& properties) {
	properties.texture->bind();

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), properties.zIndexedPosition) * glm::scale(glm::mat4(1.0f), glm::vec3(properties.dimensions.x, properties.dimensions.y, 0.0f));
	storage->quadShader->setMat4("uModelMatrix", transform);
	storage->quadShader->setVec4("uColour", properties.tint);
	storage->quadShader->setFloat("uTileFactor", properties.tilingFactor);

	storage->quadVao->bind();
	RenderCommand::drawIndexed(storage->quadVao);
	properties.texture->unbind();
}
