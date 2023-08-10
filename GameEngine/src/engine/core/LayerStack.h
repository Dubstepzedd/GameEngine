#pragma once
#include "engine/core/Layer.h"
#include <vector>
#include <algorithm>

class LayerStack {
public:
	LayerStack() = default;
	~LayerStack();
	void pushLayer(Layer* layer);
	void popLayer(Layer* layer);

	std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
	std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
	std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }

private:
	std::vector<Layer*> m_Layers;
	int m_LayerIndex = 0; //We want a stack data type, not a queue.
};