#include "TestLayer.h"
#include "Engine.h"

void TestLayer::onDetach() {
	std::cout << "Detach" << std::endl;
	delete m_Camera;
	m_Material->unbind();
}

void TestLayer::onAttach() {
	std::cout << "Attach" << std::endl;
	m_VertexArr = std::make_shared<VertexArray>();
	
	BufferLayout layout = BufferLayout {
		{ShaderDataType::FLOAT3, "aPos"},
	};

	std::shared_ptr<VertexBuffer> buff = std::make_shared<VertexBuffer>(
		std::initializer_list<float>{
			// position          
			0.5f,  0.5f, 0.0f,   // top right
			0.5f, -0.5f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f,  // top left
		}
	);

	m_VertexArr->setBuffer(buff, layout);
	
	m_IndexBuff = std::make_shared<IndexBuffer>(std::initializer_list<unsigned int>{
		0, 1, 3,   // first triangle  
		1, 2, 3    // second triangle  
	});

	AssetHandle shaderHandle = m_AssetManager->loadAsset<Shader>("default_resources/shaders/color_shader.glsl");
	AssetHandle textureHandle = m_AssetManager->loadAsset<Texture>("res/textures/studentbostäder.png");

	// Added this step to a shader (we could use reflective shaders to do this automatically in the future)
	m_AssetManager->getAsset<Shader>(shaderHandle)->setLayout(BufferLayout({
		BufferElement(ShaderDataType::FLOAT3, "aPos"),
		BufferElement(ShaderDataType::FLOAT3, "aNormal")
	}));

	m_Material = std::make_shared<Material>(shaderHandle, m_AssetManager);
	//m_Material->setTexture("uTexture", textureHandle);

    m_Mesh = new Mesh(m_VertexArr, m_IndexBuff, m_Material);
	m_Camera = new PerspectiveCameraController(glm::vec3(0, 0, 3));
	Window::getInstance().setCursorState(GLFW_CURSOR_DISABLED);
	RawModelData data = MeshLoader::loadMesh("res/models/model.obj");
	m_LoadedMesh = MeshFactory::createMesh(data, m_Material);
}

void TestLayer::onUpdate(TimeStep dt) {
	Renderer::getInstance().draw(*m_LoadedMesh, m_Model, m_Camera->getViewMatrix(), m_Camera->getProjectionMatrix(), m_AssetManager);
	//Renderer::getInstance().draw(*m_Mesh, m_Camera->getViewMatrix(), m_Camera->getProjectionMatrix(), m_AssetManager);
	m_Camera->onUpdate(dt);
}

void TestLayer::onEvent(Event& event) {
	m_Camera->onEvent(event);
}