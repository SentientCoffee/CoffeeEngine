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
	
	glm::vec4 squareColour = { 0.2f, 0.3f, 0.8f, 1.0f };

	Coffee::Ref<Coffee::Texture2D> checkerboardTexture = nullptr;
	Coffee::Ref<Coffee::Texture2D> chernoTexture = nullptr;
	
};