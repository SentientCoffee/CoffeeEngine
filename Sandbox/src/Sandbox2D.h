#pragma once

#include <Coffee.h>

class Sandbox2D : public Coffee::Layer {
public:

	Sandbox2D();
	~Sandbox2D() = default;

	void onPush() override;
	void onPop() override;
	void update(Coffee::Timestep ts) override;
	void drawImgui() override;
	void onEvent(Coffee::Event& e) override;

private:
	
	Coffee::OrthographicCameraController cameraController;

	float rows = 10.0f, columns = 10.0f, size = 0.5f;

	Coffee::Ref<Coffee::Texture2D> checkerboardTexture = nullptr;
	Coffee::Ref<Coffee::Texture2D> chernoTexture = nullptr;
	
};