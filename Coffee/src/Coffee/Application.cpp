#include "CoffeePCH.h"
#include "Coffee/Application.h"

#include <glad/glad.h>

using namespace Coffee;

Application* Application::_instance = nullptr;

static GLenum shaderDataTypeToOpenGLBaseType(const ShaderDataType type) {
	switch(type) {
		case ShaderDataType::Bool:		return GL_BOOL;
		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Float:		return GL_FLOAT;

		case ShaderDataType::Vec2:		return GL_FLOAT;
		case ShaderDataType::Vec3:		return GL_FLOAT;
		case ShaderDataType::Vec4:		return GL_FLOAT;

		case ShaderDataType::IVec2:		return GL_INT;
		case ShaderDataType::IVec3:		return GL_INT;
		case ShaderDataType::IVec4:		return GL_INT;

		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
	}

	CF_CORE_ASSERT(false, "Unknown shader data type!");
	return 0;
}

Application::Application() {
	CF_CORE_ASSERT(!_instance, "Application already exists!");
	_instance = this;
	
	_window = scope<Window>(Window::create());
	_window->setEventCallbackFunc(CF_BIND_FN(Application::onEvent));

	_imguiLayer = new ImguiLayer;
	pushOverlay(_imguiLayer);


	std::vector<float> vertices = {
		// Position				// Colour
		-0.5f, -0.5f, 0.0f,		0.8f, 0.2f, 0.8f, 1.0f,
		0.5f, -0.5f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
		0.0f,  0.5f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
	};

	std::vector<unsigned> indices = {
		0, 1, 2
	};

	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vbo = VertexBuffer::create(vertices);
	ibo = IndexBuffer::create(indices);

	const BufferLayout layout = {
		{ ShaderDataType::Vec3, "inPosition" },
		{ ShaderDataType::Vec4, "inColour" }
	};

	vbo->setLayout(layout);

	unsigned i = 0;
	for(const auto& elem : vbo->getLayout()) {
		glEnableVertexAttribArray(i);
		
		glVertexAttribPointer(i, elem.getComponentCount(),
		                      shaderDataTypeToOpenGLBaseType(elem.type),
		                      elem.normalized ? GL_TRUE : GL_FALSE,
		                      layout.getStride(), reinterpret_cast<const void*>(elem.offset));

		++i;
	}

	std::string vertSrc = R"(
		#version 450

		layout(location = 0) in vec3 inPosition;
		layout(location = 1) in vec4 inColour;
	
		layout(location = 0) out vec3 outPosition;
		layout(location = 1) out vec4 outColour;

		void main() {
			outPosition = inPosition;
			outColour = inColour;
			gl_Position = vec4(inPosition, 1.0);
		}

	)";

	std::string fragSrc = R"(
		#version 450
	
		layout(location = 0) in vec3 inPosition;
		layout(location = 1) in vec4 inColour;
		
		layout(location = 0) out vec4 outColour;

		void main() {
			outColour = vec4(inPosition * 0.5 + 0.5, 1.0);
			outColour = inColour;
		}

	)";


	shader = new Shader(vertSrc, fragSrc);
	
}

void Application::run() {

	while(_isRunning) {
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->bind();
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, nullptr);
		
		
		for(auto layer : _layerStack) {
			layer->update();
		}

		_imguiLayer->begin();
		for(auto layer : _layerStack) {
			layer->drawImgui();
		}
		_imguiLayer->end();
		
		_window->update();
	}
}

void Application::onEvent(Event& e) {
	EventDispatcher dispatcher(e);
	dispatcher.dispatch<WindowClosedEvent>(CF_BIND_FN(Application::onWindowClosed));

	for(auto it = _layerStack.end(); it != _layerStack.begin(); ) {
		(*--it)->onEvent(e);
		if(e.isHandled()) { break; }
	}
}

void Application::pushLayer(Layer* layer) {_layerStack.pushLayer(layer); }
void Application::pushOverlay(Layer* overlay) { _layerStack.pushOverlay(overlay); }

Window& Application::getWindow() const { return *_window; }
Application& Application::getInstance() { return *_instance; }

bool Application::onWindowClosed(WindowClosedEvent& e) {
	_isRunning = false;
	return true;
}
