#include "CoffeePCH.h"
#include "Coffee/Renderer/RenderCommand.h"
#include "RenderAPI/OpenGL/OpenGLRendererAPI.h"

using namespace Coffee;

RendererAPI* RenderCommand::_rendererApi = new OpenGLRendererAPI;

void RenderCommand::init() { _rendererApi->init(); }
void RenderCommand::setClearColour(const glm::vec4& colour) {_rendererApi->setClearColour(colour); }
void RenderCommand::setClearColour(const float r, const float g, const float b, const float a) { _rendererApi->setClearColour(glm::vec4(r, g, b, a)); }
void RenderCommand::clearScreen() { _rendererApi->clearScreen(); }

void RenderCommand::setViewport(const unsigned x, const unsigned y, const unsigned width, const unsigned height) { _rendererApi->setViewport(x, y, width, height); }

void RenderCommand::drawIndexed(const Ref<VertexArray>& vertexArray) { _rendererApi->drawIndexed(vertexArray); }
