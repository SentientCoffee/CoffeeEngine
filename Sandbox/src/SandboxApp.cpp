#include <Coffee.h>
#include <imgui/imgui.h>

class TestLayer : public Coffee::Layer {
public:
	
	TestLayer() : Layer("Test") {}
	~TestLayer() = default;

	void update() override {
		
	}

	void drawImgui() override {
		ImGui::Begin("TestLayer");
		ImGui::Text("Beep beep lettuce");
		ImGui::End();
	}
	
	void onEvent(Coffee::Event& e) override {
		
	}
	
};

class Sandbox : public Coffee::Application {
public:

	Sandbox() {
		pushLayer(new TestLayer());
	}
	~Sandbox() {}
	
};

Coffee::Application* Coffee::createApp() { return new Sandbox(); }