#include "TestLayer.h"

void TestLayer::onDetach() {
	std::cout << "Detach" << std::endl;
	m_Shader->unbind();


	delete m_Shader;
	delete m_VertexArr;
	delete m_Camera;
	delete m_IndexBuff;

}

void TestLayer::onAttach() {
	std::cout << "Attach" << std::endl;
	m_VertexArr = new VertexArray();

	BufferLayout layout = BufferLayout {
		{ShaderDataType::FLOAT3, "aPos"},
		{ShaderDataType::FLOAT3, "aColor"}
	};

	VertexBuffer buff = VertexBuffer {
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f,0.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f,0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   1.0f, 0.0f,0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 0.0f,0.0f  // top left 
	};

	m_VertexArr->setBuffer(buff, layout);

	m_IndexBuff = new IndexBuffer {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	//TODO Improve Resources class to have relative paths.
	m_Shader = new Shader("C:/Programming/GameEngine/GameEngine/res/shaders/shader.glsl");
	m_Camera = new PerspectiveCamera(glm::vec3(0, 0, 3));
	m_Shader->bind();
	m_Camera->updateProj(*m_Shader);

	std::cout << "Attach" << std::endl;

}

void TestLayer::onUpdate(TimeStep dt) {
	const float cameraSpeed = 0.05f; // adjust accordingly
	if (Input::getInstance().isKeyPressed(Key::W))
		m_Camera->setPos(m_Camera->getPos() += cameraSpeed * m_Camera->getFront());
	if (Input::getInstance().isKeyPressed(Key::S))
		m_Camera->setPos(m_Camera->getPos() -= cameraSpeed * m_Camera->getFront());
	if (Input::getInstance().isKeyPressed(Key::A))
		m_Camera->setPos(m_Camera->getPos() - glm::normalize(glm::cross(m_Camera->getFront(), m_Camera->getUp())) * cameraSpeed);
	if (Input::getInstance().isKeyPressed(Key::D))
		m_Camera->setPos(m_Camera->getPos() + glm::normalize(glm::cross(m_Camera->getFront(), m_Camera->getUp())) * cameraSpeed);

	m_Camera->updateView(*m_Shader);
	Renderer::draw(*m_VertexArr, *m_IndexBuff);
}

void TestLayer::onEvent(Event& event) {

}