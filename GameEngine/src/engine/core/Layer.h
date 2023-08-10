#pragma once


#include "engine/helpers/TimeStep.h"
#include "engine/events/Event.h"

class Layer {
public:
	Layer() = default;
	virtual ~Layer() = default;

	virtual void onDetach() = 0;
	virtual void onAttach() = 0;
	virtual void onUpdate(TimeStep dt) = 0;
	virtual void onEvent(Event& event) = 0;
private:

};