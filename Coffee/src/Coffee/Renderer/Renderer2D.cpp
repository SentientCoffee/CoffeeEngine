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

	static const unsigned maxQuads        = 10000;
	static const unsigned maxVertices     = maxQuads * 4;
	static const unsigned maxIndices      = maxQuads * 6;
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

	glm::vec4 quadVertexPositions[4] = {};

	Renderer2D::Statistics stats;
};

static Renderer2DData Data;

void Renderer2D::init() {
	CF_PROFILE_FUNCTION();
	
	auto* const quadIndices = new unsigned[Renderer2DData::maxIndices];
	unsigned offset = 0;
	for(unsigned i = 0; i < Renderer2DData::maxIndices; i += 6, offset += 4) {
		quadIndices[i + 0] = offset + 0;
		quadIndices[i + 1] = offset + 1;
		quadIndices[i + 2] = offset + 2;
		
		quadIndices[i + 3] = offset + 0;
		quadIndices[i + 4] = offset + 2;
		quadIndices[i + 5] = offset + 3;
	}
	
	Data.quadVboBase = new QuadVertex[Renderer2DData::maxVertices];


	Data.quadVao = VertexArray::create();
	Data.quadVbo = VertexBuffer::create(Data.maxVertices * sizeof(QuadVertex));
	const Ref<IndexBuffer> quadIbo = IndexBuffer::create(quadIndices, Data.maxIndices);

	const BufferLayout quadLayout = {
		{ ShaderDataType::Vec3,  "inPosition" },
		{ ShaderDataType::Vec4,  "inColour" },
		{ ShaderDataType::Vec2,  "inUVs" },
		{ ShaderDataType::Float, "inUVIndex" },
		{ ShaderDataType::Float, "inTileFactor" }
	};

	Data.quadVbo->setLayout(quadLayout);
	Data.quadVao->addVertexBuffer(Data.quadVbo);
	Data.quadVao->setIndexBuffer(quadIbo);
	delete[] quadIndices;
	
	Data.whiteTexture = Texture2D::create(1, 1);
	unsigned whiteData = 0xFFFFFFFF;
	Data.whiteTexture->setData(&whiteData, sizeof(unsigned));
	Data.textureSlots[0] = Data.whiteTexture;
	
	int samplers[32];
	for(int i = 0; i < Renderer2DData::maxTextureSlots; ++i) {
		samplers[i] = i;
	}
	
	Data.quadShader = Shader::create("assets/shaders/Texture.glsl");
	Data.quadShader->bind();
	Data.quadShader->setIntArray("uTextures", samplers, Data.maxTextureSlots);
	
	Data.quadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	Data.quadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
	Data.quadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
	Data.quadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
}

void Renderer2D::shutdown() {
	CF_PROFILE_FUNCTION();
}

void Renderer2D::beginScene(const OrthographicCamera& camera) {
	CF_PROFILE_FUNCTION();
	
	Data.quadShader->bind();
	Data.quadShader->setMat4("uViewProjection", camera.getViewProjectionMatrix());

	Data.quadIndexCount = 0;
	Data.quadVboPtr = Data.quadVboBase;

	Data.textureSlotIndex = 1;
}

void Renderer2D::endScene() {
	CF_PROFILE_FUNCTION();
	
	const auto dataSize = static_cast<unsigned>(reinterpret_cast<char*>(Data.quadVboPtr) - reinterpret_cast<char*>(Data.quadVboBase));
	Data.quadVbo->setData(Data.quadVboBase, dataSize);
	
	renderScene();
}

void Renderer2D::renderScene() {
	CF_PROFILE_FUNCTION();
	
	for(unsigned i = 0; i < Data.textureSlotIndex; ++i) {
		Data.textureSlots[i]->bind(i);
	}

	Data.stats.textureCount = Data.textureSlotIndex;
	
	RenderCommand::drawIndexed(Data.quadVao, Data.quadIndexCount);
	++Data.stats.drawCalls;
}

static void renderAndReset() {
	Renderer2D::endScene();
	
	Data.quadIndexCount = 0;
	Data.quadVboPtr = Data.quadVboBase;

	Data.textureSlotIndex = 1;
}

// ---------------------------------------------------------------------------
// ----- Primitives ----------------------------------------------------------
// ---------------------------------------------------------------------------

void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& dimensions, const glm::vec4& colour) {
	drawQuad({ position.x, position.y, 0.0f }, dimensions, colour);
}
void Renderer2D::drawQuad(const glm::vec2& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint, const float tilingFactor) {
	drawQuad({ position.x, position.y, 0.0f }, dimensions, texture, tint, tilingFactor);
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& dimensions, const glm::vec4& colour) {
	CF_PROFILE_FUNCTION();

	if(Data.quadIndexCount >= Renderer2DData::maxIndices) {
		renderAndReset();
	}
	
	// White texture
	const float textureIndex = 0.0f;
	const float tilingFactor = 1.0f;

	constexpr size_t quadVertexCount = 4;
	constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		glm::scale(glm::mat4(1.0f), { dimensions, 1.0f });


	for(size_t i = 0; i < quadVertexCount; ++i) {
		Data.quadVboPtr->position = transform * Data.quadVertexPositions[i];
		Data.quadVboPtr->colour = colour;
		Data.quadVboPtr->uv = textureCoords[i];
		Data.quadVboPtr->uvIndex = textureIndex;
		Data.quadVboPtr->tileFactor = tilingFactor;
		Data.quadVboPtr++;
	}

	Data.quadIndexCount += 6;
	++Data.stats.quadCount;
}

void Renderer2D::drawQuad(const glm::vec3& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint, const float tilingFactor) {
	CF_PROFILE_FUNCTION();

	if(Data.quadIndexCount >= Renderer2DData::maxIndices) {
		renderAndReset();
	}
	
	float textureIndex = 0.0f;
	constexpr size_t quadVertexCount = 4;
	constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

	for(unsigned i = 1; i < Data.textureSlotIndex; ++i) {
		if(*Data.textureSlots[i].get() == *texture.get()) {
			textureIndex = static_cast<float>(i);
		}
	}
	
	if(textureIndex == 0.0f) {
		textureIndex = static_cast<float>(Data.textureSlotIndex);
		Data.textureSlots[Data.textureSlotIndex] = texture;
		++Data.textureSlotIndex;
	}


	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		glm::scale(glm::mat4(1.0f), { dimensions, 1.0f });

	for(size_t i = 0; i < quadVertexCount; ++i) {
		Data.quadVboPtr->position = transform * Data.quadVertexPositions[i];
		Data.quadVboPtr->colour = tint;
		Data.quadVboPtr->uv = textureCoords[i];
		Data.quadVboPtr->uvIndex = textureIndex;
		Data.quadVboPtr->tileFactor = tilingFactor;
		Data.quadVboPtr++;
	}

	Data.quadIndexCount += 6;
	++Data.stats.quadCount;
}

void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& dimensions, const float rotation, const glm::vec4& colour) {
	drawRotatedQuad({ position.x, position.y, 0.0f }, dimensions, rotation, colour);
}

void Renderer2D::drawRotatedQuad(const glm::vec2& position, const glm::vec2& dimensions, const float rotation, const Ref<Texture2D>& texture, const glm::vec4& tint, float tilingFactor) {
	drawRotatedQuad({ position.x, position.y, 0.0f }, dimensions, rotation, texture, tint, tilingFactor);
}

void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& dimensions, const float rotation, const glm::vec4& colour) {
	CF_PROFILE_FUNCTION();

	if(Data.quadIndexCount >= Renderer2DData::maxIndices) {
		renderAndReset();
	}
	
	// White texture
	const float textureIndex = 0.0f;
	const float tilingFactor = 1.0f;

	constexpr size_t quadVertexCount = 4;
	constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
		glm::scale(glm::mat4(1.0f), { dimensions, 1.0f });

	for(size_t i = 0; i < quadVertexCount; ++i) {
		Data.quadVboPtr->position = transform * Data.quadVertexPositions[i];
		Data.quadVboPtr->colour = colour;
		Data.quadVboPtr->uv = textureCoords[i];
		Data.quadVboPtr->uvIndex = textureIndex;
		Data.quadVboPtr->tileFactor = tilingFactor;
		Data.quadVboPtr++;
	}

	Data.quadIndexCount += 6;
	++Data.stats.quadCount;
}

void Renderer2D::drawRotatedQuad(const glm::vec3& position, const glm::vec2& dimensions, const float rotation, const Ref<Texture2D>& texture, const glm::vec4& tint, float tilingFactor) {
	CF_PROFILE_FUNCTION();

	if(Data.quadIndexCount >= Renderer2DData::maxIndices) {
		renderAndReset();
	}

	float textureIndex = 0.0f;
	constexpr size_t quadVertexCount = 4;
	constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

	for(unsigned i = 1; i < Data.textureSlotIndex; ++i) {
		if(*Data.textureSlots[i].get() == *texture.get()) {
			textureIndex = static_cast<float>(i);
		}
	}

	if(textureIndex == 0.0f) {
		textureIndex = static_cast<float>(Data.textureSlotIndex);
		Data.textureSlots[Data.textureSlotIndex] = texture;
		++Data.textureSlotIndex;
	}

	const glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) *
		glm::scale(glm::mat4(1.0f), { dimensions, 1.0f });

	for(size_t i = 0; i < quadVertexCount; ++i) {
		Data.quadVboPtr->position = transform * Data.quadVertexPositions[i];
		Data.quadVboPtr->colour = tint;
		Data.quadVboPtr->uv = textureCoords[i];
		Data.quadVboPtr->uvIndex = textureIndex;
		Data.quadVboPtr->tileFactor = tilingFactor;
		Data.quadVboPtr++;
	}

	Data.quadIndexCount += 6;
	++Data.stats.quadCount;
}

// ---------------------------------------------------------------------------
// ----- Stats ---------------------------------------------------------------
// ---------------------------------------------------------------------------

void Renderer2D::resetStats() { memset(&Data.stats, 0, sizeof(Statistics)); }
Renderer2D::Statistics Renderer2D::getStats() { return Data.stats; }
