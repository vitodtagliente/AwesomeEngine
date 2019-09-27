#pragma once

#include <map>
#include <vector>
#include <unordered_map>
#include "system.h"
#include "type_id.h"

namespace ECS
{
	class Engine
	{
	public:

		Engine() = default;
		~Engine()
		{
			for (const auto& pair : m_systems)
			{
				delete pair.second;
			}

			m_systems.clear();
		}

		template <typename T>
		T* const addSystem()
		{
			assert(std::is_base_of<T, ISystem>());

			T* const new_system = new T();
			m_systems.insert(type<T>.id(), new_system);
			return T;
		}

		void update(const float t_deltaTime)
		{
			for (const auto& pair : m_systems)
			{
				pair.second->update(t_deltaTime);
			}
		}

	private:

		std::unordered_map<id_t, BaseSystem*> m_systems;
	};
}