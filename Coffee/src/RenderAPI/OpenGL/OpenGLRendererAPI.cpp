#include "CoffeePCH.h"
#include "RenderAPI/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

void Coffee::OpenGLRendererAPI::setClearColour(const glm::vec4& colour) { glClearColor(colour.r, colour.g, colour.b, colour.a); }
void Coffee::OpenGLRendererAPI::clearScreen() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
void Coffee::OpenGLRendererAPI::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr); }
