#include <Coffee.h>

#include <imgui/imgui.h>

class TestLayer : public Coffee::Layer {
public:
	
	TestLayer() : Layer("Test") {}
	~TestLayer() = default;

	void onPush() override {
		
		// ---------------------------------------------------------
		// ----- Triangle ------------------------------------------
		// ---------------------------------------------------------

		std::vector<float> vertices = {
			// Position				// Colour
			-0.5f, -0.5f, 0.0f,		0.8f, 0.2f, 0.8f, 1.0f,
			0.5f, -0.5f, 0.0f,		0.2f, 0.3f, 0.8f, 1.0f,
			0.0f,  0.5f, 0.0f,		0.8f, 0.8f, 0.2f, 1.0f
		};

		std::vector<unsigned> indices = {
			0, 1, 2
		};

		triVao.reset(Coffee::VertexArray::create());
		std::shared_ptr<Coffee::VertexBuffer> triVbo(Coffee::VertexBuffer::create(vertices));
		std::shared_ptr<Coffee::IndexBuffer>  triIbo(Coffee::IndexBuffer::create(indices));

		const Coffee::BufferLayout layout = {
			{ Coffee::ShaderDataType::Vec3, "inPosition" },
			{ Coffee::ShaderDataType::Vec4, "inColour" }
		};

		triVbo->setLayout(layout);
		triVao->addVertexBuffer(triVbo);
		triVao->setIndexBuffer(triIbo);

		// ---------------------------------------------------------
		// ----- Triangle Shader -----------------------------------
		// ---------------------------------------------------------

		std::string vertSrc = R"(
			#version 450

			layout(location = 0) in vec3 inPosition;
			layout(location = 1) in vec4 inColour;
	
			layout(location = 0) out vec3 outPosition;
			layout(location = 1) out vec4 outColour;

			void main() {
				outPosition = inPosition;
				outColour = inColour;
				gl_Position = vec4(inPosition, 1.0);
			}

		)";

		std::string fragSrc = R"(
			#version 450
	
			layout(location = 0) in vec3 inPosition;
			layout(location = 1) in vec4 inColour;
		
			layout(location = 0) out vec4 outColour;

			void main() {
				outColour = inColour;
			}

		)";


		triShader.reset(new Coffee::Shader(vertSrc, fragSrc));

		// ---------------------------------------------------------
		// ----- Square --------------------------------------------
		// ---------------------------------------------------------

		std::vector<float> squareVertices = {
			// Position
			-0.75f, -0.75f, 0.0f,
			0.75f, -0.75f, 0.0f,
			0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::vector<unsigned> squareIndices = {
			0, 1, 2,
			0, 2, 3
		};

		squareVao.reset(Coffee::VertexArray::create());
		std::shared_ptr<Coffee::VertexBuffer> squareVbo(Coffee::VertexBuffer::create(squareVertices));
		std::shared_ptr<Coffee::IndexBuffer>  squareIbo(Coffee::IndexBuffer::create(squareIndices));

		const Coffee::BufferLayout squareLayout = {
			{ Coffee::ShaderDataType::Vec3, "inPosition" },
		};

		squareVbo->setLayout(squareLayout);
		squareVao->addVertexBuffer(squareVbo);
		squareVao->setIndexBuffer(squareIbo);

		// ---------------------------------------------------------
		// ----- Square Shader -------------------------------------
		// ---------------------------------------------------------

		std::string squareVertSrc = R"(
			#version 450

			layout(location = 0) in vec3 inPosition;

			void main() {
				gl_Position = vec4(inPosition, 1.0);
			}

		)";

		std::string squareFragSrc = R"(
			#version 450
		
			layout(location = 0) out vec4 outColour;

			void main() {
				outColour = vec4(0.2, 0.3, 0.8, 1.0);
			}

		)";

		squareShader.reset(new Coffee::Shader(squareVertSrc, squareFragSrc));

		Coffee::RenderCommand::setClearColour(0.1f, 0.1f, 0.1f, 1.0f);
	}

	void onPop() override {
		
	}

	void update() override {
		
		Coffee::Renderer::beginScene();
		{
			squareShader->bind();
			Coffee::Renderer::submit(squareVao);

			triShader->bind();
			Coffee::Renderer::submit(triVao);
		}
		Coffee::Renderer::endScene();
		
	}

	void drawImgui() override {
		ImGui::Begin("TestLayer");
		ImGui::Text("Beep beep lettuce");
		ImGui::End();
	}
	
	void onEvent(Coffee::Event& e) override {
		
	}

private:

	std::shared_ptr<Coffee::Shader> triShader;
	std::shared_ptr<Coffee::VertexArray> triVao;

	std::shared_ptr<Coffee::Shader> squareShader;
	std::shared_ptr<Coffee::VertexArray> squareVao;
	
};

class Sandbox : public Coffee::Application {
public:

	Sandbox() {
		pushLayer(new TestLayer());
	}
	
	~Sandbox() = default;
	
};

Coffee::Application* Coffee::createApp() { return new Sandbox(); }