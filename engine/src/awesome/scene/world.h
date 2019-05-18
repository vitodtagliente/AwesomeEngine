#pragma once

#include <vector>
#include "../core/singleton.h"

namespace awesome
{
	class Object;

	class World final : public Singleton<World>
	{
	public:

		World();
		~World();

		template <typename T = Object>
		Object* const spawn()
		{

			return nullptr;
		}

	private:

		// objects
		std::vector<Object*> m_objects;
	};
}