#include "CoffeePCH.h"
#include "Coffee/Renderer/RendererAPI.h"

using namespace Coffee;

RendererAPI::API RendererAPI::_api = API::OpenGL;

RendererAPI::API RendererAPI::getAPI() { return _api; }
