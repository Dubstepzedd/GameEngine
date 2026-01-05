#include "Engine.h"
#include <memory>

class TestLayer : public Layer {
public:
	TestLayer(AssetManager& assetManager)
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
};