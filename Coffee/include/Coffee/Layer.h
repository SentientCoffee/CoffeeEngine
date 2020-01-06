#pragma once

#include "Coffee/Core.h"
#include "Coffee/Events/Event.h"

namespace Coffee {

	class Layer {
	public:

		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void onPush();
		virtual void onPop();
		virtual void update();
		virtual void onEvent(Event& e);

		const std::string& getName() const;
		
	protected:

		std::string _debugName;
	};

	class LayerStack {

		using LayerVector = std::vector<Layer*>;
		using LayerIterator = LayerVector::iterator;
		using ConstLayerIterator = LayerVector::const_iterator;
		
	public:

		LayerStack();
		~LayerStack();

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		LayerIterator begin();
		ConstLayerIterator begin() const;
		LayerIterator end();
		ConstLayerIterator end() const;
		
	private:

		LayerVector _layers;
		LayerIterator _layerInsert;
	};
	
}