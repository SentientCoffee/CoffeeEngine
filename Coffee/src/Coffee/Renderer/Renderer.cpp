#include "CoffeePCH.h"
#include "Coffee/Renderer/Renderer.h"

using namespace Coffee;

RendererAPI Renderer::_api = RendererAPI::OpenGL;

RendererAPI Renderer::getAPI() { return _api; }