#include "CoffeePCH.h"
#include "Coffee/Renderer/RenderCommand.h"
#include "RenderAPI/OpenGL/OpenGLRendererAPI.h"

using namespace Coffee;

RendererAPI* RenderCommand::_rendererApi = new OpenGLRendererAPI;

void RenderCommand::init() { _rendererApi->init(); }
void RenderCommand::setClearColour(const glm::vec4& colour) {_rendererApi->setClearColour(colour); }
void RenderCommand::setClearColour(const float r, const float g, const float b, const float a) { _rendererApi->setClearColour(glm::vec4(r, g, b, a)); }
void RenderCommand::clearScreen() { _rendererApi->clearScreen(); }

void RenderCommand::setViewport(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height) { _rendererApi->setViewport(x, y, width, height); }

void RenderCommand::drawIndexed(const Ref<VertexArray>& vertexArray, const uint32_t indexCount) { _rendererApi->drawIndexed(vertexArray, indexCount); }
