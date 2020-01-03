#include <Coffee.h>

class TestLayer : public Coffee::Layer {
public:
	
	TestLayer() : Layer("Test") {}
	~TestLayer() = default;

	void update() override {
		if(Coffee::Input::isKeyPressed(KeyCode::Escape)) {
			CF_TRACE("Escape key pressed!");
		}

		if(Coffee::Input::isMouseButtonPressed(MouseButton::Left)) {
			CF_TRACE("Left mouse button pressed!");
		}
	}
	void onEvent(Coffee::Event& e) override {
		
	}
	
};

class Sandbox : public Coffee::Application {
public:

	Sandbox() {
		pushLayer(new TestLayer());
		pushOverlay(new Coffee::ImguiLayer());
	}
	~Sandbox() {}
	
};

Coffee::Application* Coffee::createApp() { return new Sandbox(); }