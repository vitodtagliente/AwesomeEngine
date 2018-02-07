#pragma once

#include <string>
#include <vector>
#include "component.h"

namespace Awesome
{
	namespace Scenegraph
	{
		struct Object
		{
			std::string id{};

			std::vector<Component*> components;

			template <class T>
			Component* findComponent();
			template <class T>
			std::vector<Component*> findComponents();

			virtual void init() = 0;
			virtual void update(float delta_time) = 0;
			virtual void draw() = 0;

			bool operator== (const Object& other);
		};
	}
}