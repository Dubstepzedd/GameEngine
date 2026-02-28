#include "Engine.h"
#include <memory>

class TestLayer : public Layer {
public:
	TestLayer(std::shared_ptr<AssetManager> assetManager)
		: Layer(assetManager) {
	}
	virtual void onDetach() override;
	virtual void onAttach() override;
	virtual void onUpdate(TimeStep dt) override;
	virtual void onEvent(Event& event) override;

private:
	std::shared_ptr<VertexArray> m_VertexArr = nullptr;
	PerspectiveCameraController* m_Camera = nullptr;
	std::shared_ptr<IndexBuffer> m_IndexBuff = nullptr;
	BufferLayout * m_Layout = nullptr;
	VertexBuffer* m_VertexBuff = nullptr;
	std::shared_ptr<Material> m_Material = nullptr;
	Mesh* m_Mesh = nullptr;

	glm::mat4 m_Model = glm::mat4(1.0f);
	std::shared_ptr<Mesh> m_LoadedMesh = nullptr;
};