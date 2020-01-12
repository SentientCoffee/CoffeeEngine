#include "CoffeePCH.h"
#include "Coffee/Core/Layer.h"

using namespace Coffee;

Layer::Layer(const std::string& name) :
	_debugName(name) {}

void Layer::onPush() {}
void Layer::onPop() {}
void Layer::update(Timestep ts) {}
void Layer::drawImgui() {}
void Layer::onEvent(Event& e) {}

const std::string& Layer::getName() const { return _debugName; }

LayerStack::~LayerStack() {
	for(auto layer : _layers) {
		delete layer;
	}
}

void LayerStack::pushLayer(Layer* layer) {
	_layers.emplace(_layers.begin() + _layerIndex, layer);
	layer->onPush();
	++_layerIndex;
}

void LayerStack::pushOverlay(Layer* overlay) {
	_layers.emplace_back(overlay);
	overlay->onPush();
}

void LayerStack::popLayer(Layer* layer) {
	const auto it = std::find(_layers.begin(), _layers.end(), layer);
	if(it != _layers.end()) {
		(*it)->onPop();
		_layers.erase(it);
		--_layerIndex;
	}
}

void LayerStack::popOverlay(Layer* overlay) {
	const auto it = std::find(_layers.begin(), _layers.end(), overlay);
	if(it != _layers.end()) {
		(*it)->onPop();
		_layers.erase(it);
	}
}

std::vector<Layer*>::iterator LayerStack::begin() { return _layers.begin(); }
std::vector<Layer*>::const_iterator LayerStack::begin() const { return _layers.begin(); }
std::vector<Layer*>::iterator LayerStack::end() { return _layers.end(); }
std::vector<Layer*>::const_iterator LayerStack::end() const { return _layers.end(); }

