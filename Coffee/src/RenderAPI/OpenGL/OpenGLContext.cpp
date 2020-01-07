#include "CoffeePCH.h"
#include "RenderAPI/OpenGL/OpenGLContext.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

using namespace Coffee;

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :
	_windowHandle(windowHandle) {
	CF_CORE_ASSERT(windowHandle, "GLFW window does not exist!")
}

void OpenGLContext::init() {
	glfwMakeContextCurrent(_windowHandle);
	const int gladStatus = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	CF_CORE_ASSERT(gladStatus, "Could not initialize GLAD!");
}

void OpenGLContext::swapBuffers() {
	glfwSwapBuffers(_windowHandle);
}
