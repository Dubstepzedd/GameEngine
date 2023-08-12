#include "Engine.h"

class TestLayer : public Layer {
public:
	virtual void onDetach() override;
	virtual void onAttach() override;
	virtual void onUpdate(TimeStep dt) override;
	virtual void onEvent(Event& event) override;

private:
	VertexArray* m_VertexArr = nullptr;
	Shader* m_Shader = nullptr;
	PerspectiveCameraController* m_Camera = nullptr;
	IndexBuffer* m_IndexBuff = nullptr;
	BufferLayout * m_Layout = nullptr;
	VertexBuffer* m_VertexBuff = nullptr;
};