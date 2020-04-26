#pragma once

#include "Coffee/Renderer/Camera.h"
#include "Coffee/Renderer/Texture.h"

namespace Coffee {
	
	class Renderer2D {
	public:

		static void init();
		static void shutdown();

		static void beginScene(const OrthographicCamera& camera);
		static void endScene();
		static void renderScene();

		static void drawQuad(const glm::vec2& position, const glm::vec2& dimensions, const glm::vec4& colour);
		static void drawQuad(const glm::vec3& position, const glm::vec2& dimensions, const glm::vec4& colour);
		
		static void drawQuad(const glm::vec2& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f), float tilingFactor = 1.0f);
		static void drawQuad(const glm::vec3& position, const glm::vec2& dimensions, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f), float tilingFactor = 1.0f);

		static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& dimensions, float rotation, const glm::vec4& colour);
		static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& dimensions, float rotation, const glm::vec4& colour);
		
		static void drawRotatedQuad(const glm::vec2& position, const glm::vec2& dimensions, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f), float tilingFactor = 1.0f);
		static void drawRotatedQuad(const glm::vec3& position, const glm::vec2& dimensions, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tint = glm::vec4(1.0f), float tilingFactor = 1.0f);
	};
	
}
