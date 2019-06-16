#pragma once

#include <vector>
#include <awesome/core/singleton.h>
#include <awesome/math/transform.h>

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
			T * const object = Object::create<T>();
			object->transform = t_transform;
			m_objects.push_back(object);
			return object;
		}

		template <typename T = Object>
		T * const spawn(Object * const t_parent, const transform & t_transform = {})
		{
			T * const object = Object::create<T>();
			object->transform = t_transform;
			t_parent->addChild(object);
			m_objects.push_back(object);
			return object;
		}

		// get all objects in the world
		inline const std::vector<Object*>& getObjects() const { return m_objects; }

		// update
		void update(const double t_deltaTime);
		// destroy all objects
		void clear();

	private:

		// objects
		std::vector<Object*> m_objects;
	};

	template <typename T = Object>
	T * const spawn(const transform & t_transform = {})
	{
		return World::instance()->spawn<T>(t_transform);		
	}

	template <typename T = Object>
	T * const spawn(Object * const t_parent, const transform & t_transform = {})
	{
		return World::instance()->spawn<T>(t_parent, t_transform);
	}
}