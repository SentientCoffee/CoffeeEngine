#pragma once

#include "Coffee/Core/Core.h"

#include <string>

namespace Coffee {

	class Texture {
	public:

		virtual ~Texture() = default;
		
		virtual bool operator==(const Texture& other) const = 0;

		virtual void getWidth() const = 0;
		virtual void getHeight() const = 0;

		virtual void bind(unsigned slot = 0) const = 0;
		virtual void unbind(unsigned slot = 0) const = 0;

		virtual void setData(void* data, unsigned size) = 0;
	};

	class Texture2D : public Texture {
	public:

		static Ref<Texture2D> create(unsigned width, unsigned height);
		static Ref<Texture2D> create(const std::string& filepath);

		
		
	};
	
}