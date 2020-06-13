#include <Coffee.h>
#include <Coffee/EntryPoint.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>

#include "Sandbox2D.h"

class TestLayer : public Coffee::Layer {
public:
	
	TestLayer() : Layer("Test"),
	              cameraController(static_cast<float>(Coffee::Application::getInstance().getWindow().getWidth()) / static_cast<float>(Coffee::Application::getInstance().getWindow().getHeight())) {}
	
	~TestLayer() = default;

	void onPush() override {

		// ---------------------------------------------------------
		// ----- Square --------------------------------------------
		// ---------------------------------------------------------

		std::vector<float> squareVertices = {
			// Position				// UV coords
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
		};

		std::vector<uint32_t> squareIndices = {
			0, 1, 2,
			0, 2, 3
		};

		squareVao = Coffee::VertexArray::create();
		Coffee::Ref<Coffee::VertexBuffer> squareVbo(Coffee::VertexBuffer::create(squareVertices));
		const Coffee::Ref<Coffee::IndexBuffer> squareIbo(Coffee::IndexBuffer::create(squareIndices));

		const Coffee::BufferLayout squareLayout = {
			{ Coffee::ShaderDataType::Vec3, "inPosition" },
			{ Coffee::ShaderDataType::Vec2, "inUVs" }
		};

		squareVbo->setLayout(squareLayout);
		squareVao->addVertexBuffer(squareVbo);
		squareVao->setIndexBuffer(squareIbo);

		// ---------------------------------------------------------
		// ----- Square Shader -------------------------------------
		// ---------------------------------------------------------

		const auto squareShader = Coffee::Renderer::getShaderLibrary()->load("assets/shaders/texture.glsl");

		// ---------------------------------------------------------
		// ----- Square Texture ------------------------------------
		// ---------------------------------------------------------

		checkerboardTexture = Coffee::Texture2D::create("assets/textures/checkerboard.png");
		chernoTexture = Coffee::Texture2D::create("assets/textures/ChernoLogo.png");

		squareShader->bind();
		squareShader->setInt("uTextureAlbedo", 0);

		Coffee::RenderCommand::setClearColour(0.1f, 0.1f, 0.1f, 1.0f);
	}

	void onPop() override {
		
	}

	void update(const Coffee::Timestep ts) override {

		cameraController.onUpdate(ts);
		
		if(Coffee::Input::isKeyPressed(KeyCode::J)) {
			squarePos.x -= squareSpeed * ts;
		}
		else if(Coffee::Input::isKeyPressed(KeyCode::L)) {
			squarePos.x += squareSpeed * ts;
		}

		if(Coffee::Input::isKeyPressed(KeyCode::I)) {
			squarePos.y += squareSpeed * ts;
		}
		else if(Coffee::Input::isKeyPressed(KeyCode::K)) {
			squarePos.y -= squareSpeed * ts;
		}

		
		Coffee::Renderer::beginScene(cameraController.getCamera());
		{
			const auto squareShader = Coffee::Renderer::getShaderLibrary()->get("texture");
			const auto transform = glm::translate(glm::mat4(1.0f), squarePos) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f));
			
			checkerboardTexture->bind();
			Coffee::Renderer::submit(squareShader, squareVao, transform);
			chernoTexture->bind();
			Coffee::Renderer::submit(squareShader, squareVao,transform);
		}
		Coffee::Renderer::endScene();
		
	}

	void drawImgui() override {}
	
	void onEvent(Coffee::Event& e) override {
		cameraController.onEvent(e);
	}

private:

	Coffee::Ref<Coffee::VertexArray> squareVao;

	Coffee::Ref<Coffee::Texture2D> checkerboardTexture;
	Coffee::Ref<Coffee::Texture2D> chernoTexture;
	
	Coffee::OrthographicCameraController cameraController;

	glm::vec3 squarePos = { 0.0f, 0.0f, 0.0f };
	float squareSpeed = 1.0f;

	glm::vec3 squareColour = { 0.2f, 0.3f, 0.8f };
	
};

class Sandbox : public Coffee::Application {
public:

	Sandbox() {
		//pushLayer(new TestLayer());
		pushLayer(new Sandbox2D());
	}
	
	~Sandbox() = default;
	
};

Coffee::Application* Coffee::createApp() { return new Sandbox(); }