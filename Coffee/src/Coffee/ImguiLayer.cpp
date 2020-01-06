#include "CoffeePCH.h"
#include "Coffee/ImguiLayer.h"

#include "Coffee/Application.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace Coffee;

ImguiLayer::ImguiLayer() : Layer("ImguiLayer") {}

void ImguiLayer::onPush() {
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
	io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	ImGui_ImplOpenGL3_Init("#version 450");
}
void ImguiLayer::onPop() {}

void ImguiLayer::update() {
	ImGuiIO& io = ImGui::GetIO();
	Application& app = Application::getInstance();
	io.DisplaySize = ImVec2(static_cast<float>(app.getWindow().getWidth()), static_cast<float>(app.getWindow().getHeight()));
	
	const float time = static_cast<float>(glfwGetTime());
	io.DeltaTime = _currentTime > 0.0f ? (time - _currentTime) : 1.0f / 60.0f;
	_currentTime = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
	
	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiLayer::onEvent(Event& e) {
	EventDispatcher dispatcher(e);
	
	dispatcher.dispatch<MouseButtonPressedEvent>(CF_BIND_FN(ImguiLayer::onMouseButtonPressed));
	dispatcher.dispatch<MouseButtonReleasedEvent>(CF_BIND_FN(ImguiLayer::onMouseButtonReleased));
	dispatcher.dispatch<MouseMovedEvent>(CF_BIND_FN(ImguiLayer::onMouseMoved));
	dispatcher.dispatch<MouseScrolledEvent>(CF_BIND_FN(ImguiLayer::onMouseScrolled));
	
	dispatcher.dispatch<KeyPressedEvent>(CF_BIND_FN(ImguiLayer::onKeyPressed));
	dispatcher.dispatch<KeyReleasedEvent>(CF_BIND_FN(ImguiLayer::onKeyReleased));
	dispatcher.dispatch<KeyTypedEvent>(CF_BIND_FN(ImguiLayer::onKeyTyped));

	dispatcher.dispatch<WindowResizedEvent>(CF_BIND_FN(ImguiLayer::onWindowResized));
}

bool ImguiLayer::onMouseButtonPressed(MouseButtonPressedEvent& e) {
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[e.getMouseButton()] = true;
	
	return false;
}

bool ImguiLayer::onMouseButtonReleased(MouseButtonReleasedEvent& e) {
	ImGuiIO& io = ImGui::GetIO();
	io.MouseDown[e.getMouseButton()] = false;

	return false;
}

bool ImguiLayer::onMouseMoved(MouseMovedEvent& e) {
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = { e.getMouseX(), e.getMouseY() };

	return false;
}
bool ImguiLayer::onMouseScrolled(MouseScrolledEvent& e) {
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheel += e.getYOffset();
	io.MouseWheelH += e.getXOffset();

	return false;
}

bool ImguiLayer::onKeyPressed(KeyPressedEvent& e) {
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[e.getKeyCode()] = true;

	io.KeyCtrl  = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT]   || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt   = io.KeysDown[GLFW_KEY_LEFT_ALT]     || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER]   || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
	
	return false;
}

bool ImguiLayer::onKeyReleased(KeyReleasedEvent& e) {
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[e.getKeyCode()] = false;
	
	return false;
}

bool ImguiLayer::onKeyTyped(KeyTypedEvent& e) {
	ImGuiIO& io = ImGui::GetIO();
	const unsigned keyCode = e.getKeyCode();

	if(keyCode > 0 && keyCode < 0x10000) {
		io.AddInputCharacter(static_cast<unsigned short>(keyCode));
	}

	return false;
}

bool ImguiLayer::onWindowResized(WindowResizedEvent& e) {
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(static_cast<float>(e.getWidth()), static_cast<float>(e.getHeight()));
	io.DisplayFramebufferScale = { 1.0f, 1.0f };
	glViewport(0, 0, e.getWidth(), e.getHeight());

	return false;
}
