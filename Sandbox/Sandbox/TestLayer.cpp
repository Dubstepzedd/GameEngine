#include "TestLayer.h"
#include "Engine.h"

void TestLayer::onDetach() {
	std::cout << "Detach" << std::endl;
	Renderer::getInstance().unbindShader();
	delete m_Shader;
	delete m_VertexArr;
	delete m_Camera;
	delete m_IndexBuff;
	delete m_Texture;
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
	
	m_VertexArr->setBuffer(buff, layout);

	m_IndexBuff = new IndexBuffer{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	m_Shader = new Shader("default_resources/shaders/texture_shader.glsl");
	
	Renderer::getInstance().bindShader(m_Shader);
	m_Texture = new Texture(
		"res/textures/texture.jpg"
	);

	m_Shader->setSamplerUniform("uTexture", 0);
	m_Camera = new PerspectiveCameraController(glm::vec3(0, 0, 3));
	Window::getInstance().setCursorState(GLFW_CURSOR_DISABLED);

}

void TestLayer::onUpdate(TimeStep dt) {
	m_Texture->bind(0);
	Renderer::getInstance().draw(*m_VertexArr, *m_IndexBuff);
	m_Camera->onUpdate(dt);
	m_Texture->unbind();
}

void TestLayer::onEvent(Event& event) {
	m_Camera->onEvent(event);
}