#include "CoffeePCH.h"
#include "Coffee/Renderer/Renderer2D.h"

#include "Coffee/Renderer/Shader.h"
#include "Coffee/Renderer/VertexArray.h"
#include "Coffee/Renderer/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Coffee;

struct QuadVertex {
	glm::vec3 position = { 0.0f, 0.0f, 0.0f };
	glm::vec4 colour   = { 1.0f, 1.0f, 1.0f, 1.0f };
	glm::vec2 uv       = { 0.0f, 0.0f };
	float uvIndex      = 0.0f;
	float tileFactor   = 1.0f;
};

struct Renderer2DData {

	const unsigned maxQuads = 10000;
	const unsigned maxVertices = maxQuads * 4;
	const unsigned maxIndices = maxQuads * 6;
	static const unsigned maxTextureSlots = 32; // TODO: RenderCaps

	unsigned quadIndexCount = 0;

	QuadVertex* quadVboBase = nullptr;
	QuadVertex* quadVboPtr  = nullptr;

	Ref<VertexArray> quadVao = nullptr;
	Ref<VertexBuffer> quadVbo = nullptr;
	Ref<Shader> quadShader = nullptr;
	Ref<Texture2D> whiteTexture = nullptr;

	std::array<Ref<Texture2D>, maxTextureSlots> textureSlots = {};
	unsigned textureSlotIndex = 1;

	glm::vec4 quadVertexPositions[4];
};

static Renderer2DData storage;

void Renderer2D::init() {

	unsigned* quadIndices = new unsigned[storage.maxIndices];
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
		{ ShaderDataType::Vec3,  "inPosition" },
		{ ShaderDataType::Vec4,  "inColour" },
		{ ShaderDataType::Vec2,  "inUVs" },
		{ ShaderDataType::Float, "inUVIndex" },
		{ ShaderDataType::Float, "inTileFactor" }
	};

	storage.quadVbo->setLayout(quadLayout);
	storage.quadVao->addVertexBuffer(storage.quadVbo);
	storage.quadVao->setIndexBuffer(quadIbo);
	delete[] quadIndices;
	
	storage.quadShader = Shader::create("assets/shaders/Texture.glsl");

	storage.quadShader->bind();
	storage.quadShader->setInt("uTextureAlbedo", 0);
	
	storage.whiteTexture = Texture2D::create(1, 1);
	unsigned whiteData = 0xFFFFFFFF;
	storage.whiteTexture->setData(&whiteData, sizeof(unsigned));

	int samplers[32];
	for(int i = 0; i < Renderer2DData::maxTextureSlots; ++i) {
		samplers[i] = i;
	}
	storage.quadShader->setIntArray("uTextures", samplers, storage.maxTextureSlots);

	
	storage.textureSlots[0] = storage.whiteTexture;

	storage.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	storage.quadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
	storage.quadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
	storage.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
}

void Renderer2D::shutdown() {}

void Renderer2D::beginScene(const OrthographicCamera& camera) {
	
	storage.quadShader->bind();
	storage.quadShader->setMat4("uViewProjection", camera.getViewProjectionMatrix());

	storage.quadIndexCount = 0;
	storage.quadVboPtr = storage.quadVboBase;

	storage.textureSlotIndex = 1;
}

void Renderer2D::endScene() {
	const auto dataSize = static_cast<unsigned>(reinterpret_cast<char*>(storage.quadVboPtr) - reinterpret_cast<char*>(storage.quadVboBase));
	storage.quadVbo->setData(storage.quadVboBase, dataSize);
	
	renderScene();
}

void Renderer2D::renderScene() {
	for(unsigned i = 0; i < storage.textureSlotIndex; ++i) {
		storage.textureSlots[i]->bind(i);
	}
	
	RenderCommand::drawIndexed(storage.quadVao, storage.quadIndexCount);
}

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& dimensions, const glm::vec4& colour) {
	drawQuad({ position.x, position.y, 0.0f }, dimensions, colour);
}
void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint, const float tilingFactor) {
	drawQuad({ position.x, position.y, 0.0f }, dimensions, texture, tint, tilingFactor);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& dimensions, const glm::vec4& colour) {
	// White texture
	const float textureIndex = 0.0f;
	const float tileFactor = 1.0f;

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		glm::scale(glm::mat4(1.0f), { dimensions, 1.0f });

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[0];
	storage.quadVboPtr->colour = colour;
	storage.quadVboPtr->uv = { 0.0f, 0.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tileFactor;
	storage.quadVboPtr++;

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[1];
	storage.quadVboPtr->colour = colour;
	storage.quadVboPtr->uv = { 1.0f, 0.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tileFactor;
	storage.quadVboPtr++;

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[2];
	storage.quadVboPtr->colour = colour;
	storage.quadVboPtr->uv = { 1.0f, 1.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tileFactor;
	storage.quadVboPtr++;

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[3];
	storage.quadVboPtr->colour = colour;
	storage.quadVboPtr->uv = { 0.0f, 1.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tileFactor;
	storage.quadVboPtr++;

	storage.quadIndexCount += 6;
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint, const float tilingFactor) {
	float textureIndex = 0.0f;

	for(unsigned i = 1; i < storage.textureSlotIndex; ++i) {
		if(*storage.textureSlots[i].get() == *texture.get()) {
			textureIndex = static_cast<float>(i);
		}
	}
	
	if(textureIndex == 0.0f) {
		textureIndex = static_cast<float>(storage.textureSlotIndex);
		storage.textureSlots[storage.textureSlotIndex] = texture;
		++storage.textureSlotIndex;
	}

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		glm::scale(glm::mat4(1.0f), { dimensions, 1.0f });
	
	storage.quadVboPtr->position = transform * storage.quadVertexPositions[0];
	storage.quadVboPtr->colour = tint;
	storage.quadVboPtr->uv = { 0.0f, 0.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tilingFactor;
	storage.quadVboPtr++;

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[1];
	storage.quadVboPtr->colour = tint;
	storage.quadVboPtr->uv = { 1.0f, 0.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tilingFactor;
	storage.quadVboPtr++;

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[2];
	storage.quadVboPtr->colour = tint;
	storage.quadVboPtr->uv = { 1.0f, 1.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tilingFactor;
	storage.quadVboPtr++;

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[3];
	storage.quadVboPtr->colour = tint;
	storage.quadVboPtr->uv = { 0.0f, 1.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tilingFactor;
	storage.quadVboPtr++;

	storage.quadIndexCount += 6;
}

void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& dimensions, const float rotation, const glm::vec4& colour) {
	drawRotatedQuad({ position.x, position.y, 0.0f }, dimensions, rotation, colour);
}

void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& dimensions, const float rotation, const Ref<Texture2D>& texture, const glm::vec4& tint, float tilingFactor) {
	drawRotatedQuad({ position.x, position.y, 0.0f }, dimensions, rotation, texture, tint, tilingFactor);
}

void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& dimensions, const float rotation, const glm::vec4& colour) {
	// White texture
	const float textureIndex = 0.0f;
	const float tileFactor = 1.0f;

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
		glm::scale(glm::mat4(1.0f), { dimensions, 1.0f });

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[0];
	storage.quadVboPtr->colour = colour;
	storage.quadVboPtr->uv = { 0.0f, 0.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tileFactor;
	storage.quadVboPtr++;

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[1];
	storage.quadVboPtr->colour = colour;
	storage.quadVboPtr->uv = { 1.0f, 0.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tileFactor;
	storage.quadVboPtr++;

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[2];
	storage.quadVboPtr->colour = colour;
	storage.quadVboPtr->uv = { 1.0f, 1.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tileFactor;
	storage.quadVboPtr++;

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[3];
	storage.quadVboPtr->colour = colour;
	storage.quadVboPtr->uv = { 0.0f, 1.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tileFactor;
	storage.quadVboPtr++;

	storage.quadIndexCount += 6;
}

void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& dimensions, const float rotation, const Ref<Texture2D>& texture, const glm::vec4& tint, float tilingFactor) {
	float textureIndex = 0.0f;

	for(unsigned i = 1; i < storage.textureSlotIndex; ++i) {
		if(*storage.textureSlots[i].get() == *texture.get()) {
			textureIndex = static_cast<float>(i);
		}
	}

	if(textureIndex == 0.0f) {
		textureIndex = static_cast<float>(storage.textureSlotIndex);
		storage.textureSlots[storage.textureSlotIndex] = texture;
		++storage.textureSlotIndex;
	}

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
		glm::scale(glm::mat4(1.0f), { dimensions, 1.0f });

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[0];
	storage.quadVboPtr->colour = tint;
	storage.quadVboPtr->uv = { 0.0f, 0.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tilingFactor;
	storage.quadVboPtr++;

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[1];
	storage.quadVboPtr->colour = tint;
	storage.quadVboPtr->uv = { 1.0f, 0.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tilingFactor;
	storage.quadVboPtr++;

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[2];
	storage.quadVboPtr->colour = tint;
	storage.quadVboPtr->uv = { 1.0f, 1.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tilingFactor;
	storage.quadVboPtr++;

	storage.quadVboPtr->position = transform * storage.quadVertexPositions[3];
	storage.quadVboPtr->colour = tint;
	storage.quadVboPtr->uv = { 0.0f, 1.0f };
	storage.quadVboPtr->uvIndex = textureIndex;
	storage.quadVboPtr->tileFactor = tilingFactor;
	storage.quadVboPtr++;

	storage.quadIndexCount += 6;
}
