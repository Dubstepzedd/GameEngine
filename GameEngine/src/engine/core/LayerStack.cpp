#include "engine/core/LayerStack.h"

LayerStack::~LayerStack() {
	for (Layer* layer : m_Layers) {
		layer->onDetach();
		delete layer;
	}
}

void LayerStack::popLayer(Layer* layer) {
	std::vector<Layer*>::iterator it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerIndex, layer);

	//If the Layer* was found in the std::vector.
	if (it != m_Layers.begin() + m_LayerIndex) {
		layer->onDetach();
		m_Layers.erase(it);
		m_LayerIndex--;
	}
}

void LayerStack::pushLayer(Layer* layer) {
	m_Layers.emplace(m_Layers.begin() + m_LayerIndex, layer);
	layer->onAttach();
	m_LayerIndex++;
}