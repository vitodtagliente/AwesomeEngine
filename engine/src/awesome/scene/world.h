#pragma once

#include <vector>
#include "../core/singleton.h"
#include "../math/transform.h"

namespace awesome
{
	class Object;

	class World final : public Singleton<World>
	{
	public:

		World();
		~World();

		template <typename T = Object>
		T * const spawn(const transform & t_transform = {})
		{
			T * const object = new T();
			object->transform = t_transform;
			m_objects.push_back(object);
			return object;
		}

		template <typename T = Object>
		T * const spawn(Object * const t_parent, const transform & t_transform = {})
		{
			T * const object = new T();
			object->transform = t_transform;
			t_parent->addChild(object);
			m_objects.push_back(object);
			return object;
		}

		// get all objects in the world
		inline const std::vector<Object*>& getObjects() const { return m_objects; }

		// destroy all objects
		void clear();

	private:

		// objects
		std::vector<Object*> m_objects;
	};
}