#include "Engine.h"

class TestLayer : public Layer {
public:
	virtual void onDetach() override;
	virtual void onAttach() override;
	virtual void onUpdate(TimeStep dt) override;
	virtual void onEvent(Event& event) override;
};