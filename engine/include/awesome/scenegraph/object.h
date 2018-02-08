#pragma once

#include <string>
#include <vector>
#include "component.h"
#include "transform.h"

namespace Awesome
{
	namespace Scenegraph
	{
		struct Object
		{
			std::string id{};

			Transform transform;

			std::vector<Component*> components;

			template <class T>
			Component* findComponent();
			template <class T>
			std::vector<Component*> findComponents();

			/*
			template <class T>
			Component* findComponentInChildren();
			template <class T>
			std::vector<Component*> findComponentsInChildren();
			*/

			virtual void init();
			virtual void update(float delta_time);

			bool operator== (const Object& other);
		};
	}
}