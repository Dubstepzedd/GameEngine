#pragma once
#include "engine/io/AssetManager.h"
#include "engine/helpers/TimeStep.h"
#include "engine/events/Event.h"

class Layer {
public:
	explicit Layer(std::shared_ptr<AssetManager> assetManager) : m_AssetManager(assetManager) {}
	virtual ~Layer() = default;

	virtual void onDetach() = 0;
	virtual void onAttach() = 0;
	virtual void onUpdate(TimeStep dt) = 0;
	virtual void onEvent(Event& event) = 0;
protected:
	std::shared_ptr<AssetManager> m_AssetManager;
};