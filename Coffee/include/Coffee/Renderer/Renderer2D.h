#pragma once

#include "Coffee/Renderer/CameraController.h"
#include "Coffee/Renderer/Texture.h"

namespace Coffee {

	struct ColouredQuad {
		union {
			glm::vec3 zIndexedPosition;
			struct {
				glm::vec2 position;
				float zIndex;
			};
		};
		glm::vec2 dimensions;
		glm::vec4 colour;

		ColouredQuad(const glm::vec3& position, const glm::vec2& dimensions, const glm::vec4& colour);
		ColouredQuad(const glm::vec2& position, const glm::vec2& dimensions, const glm::vec4& colour);
		ColouredQuad(const glm::vec2& position, float zIndex, const glm::vec2& dimensions, const glm::vec4& colour);
	};

	struct TexturedQuad {
		union {
			glm::vec3 zIndexedPosition;
			struct {
				glm::vec2 position;
				float zIndex;
			};
		};
		glm::vec2 dimensions;
		Ref<Texture2D> texture;
		glm::vec4 tint = { 1.0f, 1.0f, 1.0f, 1.0f };
		float tilingFactor = 1.0f;

		TexturedQuad(const glm::vec3& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f), float tilingFactor = 1.0f);
		TexturedQuad(const glm::vec2& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f), float tilingFactor = 1.0f);
		TexturedQuad(const glm::vec2& position, float zIndex, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f), float tilingFactor = 1.0f);
	};
	
	class Renderer2D {
	public:

		static void init();
		static void shutdown();

		static void beginScene(const OrthographicCamera& camera);
		static void endScene();

		static void drawQuad(const glm::vec2& position, const glm::vec2& dimensions, const glm::vec4& colour);
		static void drawQuad(const glm::vec2& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f));
		
		static void drawQuad(const glm::vec3& position, const glm::vec2& dimensions, const glm::vec4& colour);
		static void drawQuad(const glm::vec3& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f));

		static void drawQuad(const ColouredQuad& properties);
		static void drawQuad(const TexturedQuad& properties);
	};
	
}
