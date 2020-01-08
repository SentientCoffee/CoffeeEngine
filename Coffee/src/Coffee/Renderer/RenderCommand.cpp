#include "CoffeePCH.h"
#include "Coffee/Renderer/RenderCommand.h"
#include "RenderAPI/OpenGL/OpenGLRendererAPI.h"

using namespace Coffee;

RendererAPI* RenderCommand::_rendererApi = new OpenGLRendererAPI;

void RenderCommand::setClearColour(const glm::vec4& colour) {_rendererApi->setClearColour(colour); }
void RenderCommand::setClearColour(const float r, const float g, const float b, const float a) { _rendererApi->setClearColour(glm::vec4(r, g, b, a)); }
void RenderCommand::clearScreen() { _rendererApi->clearScreen(); }
void RenderCommand::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { _rendererApi->drawIndexed(vertexArray); }
