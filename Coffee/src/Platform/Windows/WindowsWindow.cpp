#include "CoffeePCH.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Coffee/Events/AppEvents.h"
#include "Coffee/Events/KeyEvents.h"
#include "Coffee/Events/MouseEvents.h"

#include <glad/glad.h>


using namespace Coffee;

static bool glfwInitialized = false;

Window* Window::create(const WindowProperties& properties) {
	return new WindowsWindow(properties);
}

WindowProperties::WindowProperties(const std::string& title, const unsigned width, const unsigned height) :
	title(title), width(width), height(height) {}

WindowsWindow::WindowsWindow(const WindowProperties& properties) :
	_window(nullptr) {
	WindowsWindow::init(properties);
}
WindowsWindow::~WindowsWindow() {
	WindowsWindow::shutdown();
}

void WindowsWindow::init(const WindowProperties& properties) {
	_data.title = properties.title;
	_data.width = properties.width;
	_data.height = properties.height;

	#if CF_DEBUG
	CF_CORE_INFO("Creating Windows window \"{0}\" ({1} x {2})", _data.title, _data.width, _data.height);
	#endif

	// GLFW initialization
	if(!glfwInitialized) {
		const int glfwStatus = glfwInit();
		CF_CORE_ASSERT(glfwStatus, "Could not initialize GLFW!");
		glfwSetErrorCallback(glfwErrorCallback);
		glfwInitialized = true;
	}

	_window = glfwCreateWindow(static_cast<int>(_data.width),
	                           static_cast<int>(_data.height),
	                           _data.title.c_str(),
	                           nullptr, nullptr);

	glfwMakeContextCurrent(_window);
	glfwSetWindowUserPointer(_window, &_data);
	setVSync(true);
	setGlfwCallbacks();

	// GLAD function loading
	const int gladStatus = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	CF_CORE_ASSERT(gladStatus, "Could not initialize GLAD!");
}
void WindowsWindow::shutdown() {
	glfwDestroyWindow(_window);
}

void WindowsWindow::setGlfwCallbacks() {
	// Window resize callback
	glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, const int width, const int height) {
		const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		data->width = width;
		data->height = height;

		WindowResizedEvent e(width, height);
		data->eventFunc(e);
	});

	// Window close callback
	glfwSetWindowCloseCallback(_window, [](GLFWwindow* window) {
		const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		WindowClosedEvent e;
		data->eventFunc(e);
	});

	// Window key callback
	glfwSetKeyCallback(_window, [](GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
		const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
		static int repeatCount = 0;
		
		switch(action) {
			case GLFW_PRESS:
			{
				KeyPressedEvent keyPressed(key, 0);
				data->eventFunc(keyPressed);
				break;
			}
			case GLFW_RELEASE:
			{
				repeatCount = 0;
				KeyReleasedEvent keyReleased(key);
				data->eventFunc(keyReleased);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent keyRepeat(key, ++repeatCount);
				data->eventFunc(keyRepeat);
				break;
			}
			default: break;
		}
	});

	glfwSetCharCallback(_window, [](GLFWwindow* window, const unsigned int key) {
		const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		KeyTypedEvent keyTyped(static_cast<int>(key));
		data->eventFunc(keyTyped);
		
	});

	// Window mouse button callback
	glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, const int button, const int action, const int mods) {
		const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		switch(action) {
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent mousePressed(button);
				data->eventFunc(mousePressed);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent mouseReleased(button);
				data->eventFunc(mouseReleased);
				break;
			}
			default: break;
		}
	});

	// Window mouse scrolling callback
	glfwSetScrollCallback(_window, [](GLFWwindow* window, const double xOffset, const double yOffset) {
		const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		MouseScrolledEvent e(static_cast<float>(xOffset), static_cast<float>(yOffset));
		data->eventFunc(e);
	});

	// Window mouse position callback
	glfwSetCursorPosCallback(_window, [](GLFWwindow* window, const double xPos, const double yPos) {
		const auto data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));

		MouseMovedEvent e(static_cast<float>(xPos), static_cast<float>(yPos));
		data->eventFunc(e);
	});
}

void WindowsWindow::glfwErrorCallback(const int errorCode, const char* log) {
	CF_CORE_CRITICAL("GLFW ERROR! ({0})\n{1}", errorCode, log);
}

void WindowsWindow::update() {
	glfwPollEvents();
	glfwSwapBuffers(_window);
}

unsigned WindowsWindow::getWidth() const { return _data.width; }
unsigned WindowsWindow::getHeight() const { return _data.height; }

void WindowsWindow::setVSync(const bool enabled) {
	_data.isVSync = enabled;

	if(_data.isVSync) {	glfwSwapInterval(1); }
	else              { glfwSwapInterval(0); }
}
bool WindowsWindow::isVSync() const { return _data.isVSync; }
void* WindowsWindow::getNativeWindow() const { return _window; }

void WindowsWindow::setEventCallbackFunc(const EventCallbackFunc& callback) { _data.eventFunc = callback; }

