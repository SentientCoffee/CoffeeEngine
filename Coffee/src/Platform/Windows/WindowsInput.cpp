#include "CoffeePCH.h"
#include "Platform/Windows/WindowsInput.h"

#include "Coffee/Application.h"

#include <glfw/glfw3.h>

using namespace Coffee;

Input* Input::_instance = new WindowsInput;

bool WindowsInput::isKeyPressedImpl(const int keyCode) {
	const auto window = Application::getInstance().getWindow().getNativeWindow();
	const int state = glfwGetKey(static_cast<GLFWwindow*>(window), keyCode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::isMouseButtonPressedImpl(const int button) {
	const auto window = Application::getInstance().getWindow().getNativeWindow();
	const int state = glfwGetMouseButton(static_cast<GLFWwindow*>(window), button);
	return state == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::getMousePosImpl() {
	const auto window = Application::getInstance().getWindow().getNativeWindow();
	double xPos, yPos;
	glfwGetCursorPos(static_cast<GLFWwindow*>(window), &xPos, &yPos);

	return { static_cast<float>(xPos), static_cast<float>(yPos) };
}

float WindowsInput::getMouseXImpl() {
	auto [x, y] = getMousePosImpl();
	return x;
}
float WindowsInput::getMouseYImpl() {
	auto [x, y] = getMousePosImpl();
	return y;
}
