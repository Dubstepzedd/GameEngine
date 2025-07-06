#include "TestLayer.h"
#include "Engine.h"

void TestLayer::onDetach() {
	std::cout << "Detach" << std::endl;
	delete m_VertexArr;
	delete m_Camera;
	delete m_IndexBuff;
	m_Material->unbind();
}

void TestLayer::onAttach() {
	std::cout << "Attach" << std::endl;
	m_VertexArr = new VertexArray();

	BufferLayout layout = BufferLayout {
		{ShaderDataType::FLOAT3, "aPos"},
		{ShaderDataType::FLOAT2, "aTexCoord"},
	};

	VertexBuffer buff = VertexBuffer {
		// position         // color            // texCoord
		0.5f,  0.5f, 0.0f,  /*1.0f, 0.0f, 0.0f,*/   1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f,  /*1.0f, 0.0f, 0.0f,*/   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, /*1.0f, 0.0f, 0.0f,*/   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f, /*1.0f, 0.0f, 0.0f,*/   0.0f, 1.0f  // top left
	};
	
	AssetHandle shaderHandle = m_AssetManager.loadAsset<Shader>("default_resources/shaders/texture_shader.glsl");
	AssetHandle textureHandle = m_AssetManager.loadAsset<Texture>("res/textures/texture.jpg");
	spdlog::info("Shader handle: {}", shaderHandle.toString()); // Looks good
	spdlog::info("Texture handle: {}", textureHandle.toString()); // Looks good

	m_VertexArr->setBuffer(buff, layout);

	m_IndexBuff = new IndexBuffer{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	m_Material = new Material(shaderHandle);
	m_Material->setTexture("uTexture", textureHandle);
	m_Camera = new PerspectiveCameraController(glm::vec3(0, 0, 3));
	Window::getInstance().setCursorState(GLFW_CURSOR_DISABLED);
}

void TestLayer::onUpdate(TimeStep dt) {
	Renderer::getInstance().draw(*m_VertexArr, *m_IndexBuff, *m_Material, m_Camera->getViewMatrix(), m_Camera->getProjectionMatrix(), m_AssetManager);
	m_Camera->onUpdate(dt);
}

void TestLayer::onEvent(Event& event) {
	m_Camera->onEvent(event);
}