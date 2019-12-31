#include <Coffee.h>

class TestLayer : public Coffee::Layer {
public:
	
	TestLayer() : Layer("Test") {}
	~TestLayer() = default;

	void update() override { return; }
	void onEvent(Coffee::Event& e) override { CF_TRACE("{0}", e); }
	
};

class Sandbox : public Coffee::Application {
public:

	Sandbox() { pushLayer(new TestLayer()); }
	~Sandbox() {}
	
};

Coffee::Application* Coffee::createApp() { return new Sandbox(); }