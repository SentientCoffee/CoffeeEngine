#include "CoffeePCH.h"
#include "RenderAPI/OpenGL/OpenGLContext.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>

using namespace Coffee;

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) :
	_windowHandle(windowHandle)
{
	CF_CORE_ASSERT(windowHandle, "GLFW window does not exist!")
}

void OpenGLContext::init() {
	CF_PROFILE_FUNCTION();
	
	glfwMakeContextCurrent(_windowHandle);
	const int gladStatus = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	CF_CORE_ASSERT(gladStatus, "Could not initialize GLAD!");

	CF_CORE_INFO("OpenGL Info:");
	CF_CORE_INFO("\tVendor:       {0}", glGetString(GL_VENDOR));
	CF_CORE_INFO("\tRenderer:     {0}", glGetString(GL_RENDERER));
	CF_CORE_INFO("\tVersion:      {0}", glGetString(GL_VERSION));
	CF_CORE_INFO("\tGLSL Version: {0}", glGetString(GL_SHADING_LANGUAGE_VERSION));

	#if CF_ENABLE_ASSERTS

	int versionMajor = 0, versionMinor = 0;
	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

	CF_CORE_ASSERT(versionMajor > 4 || versionMajor == 4 && versionMinor >= 5, "CoffeeEngine requires at least OpenGL version 4.5!");
	
	#endif
}

void OpenGLContext::swapBuffers() {
	CF_PROFILE_FUNCTION();
	glfwSwapBuffers(_windowHandle);
}
