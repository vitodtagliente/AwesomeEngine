#pragma once

#include <map>
#include <vector>
#include <unordered_map>
#include "system.h"

namespace ECS
{
	class Engine
	{
	public:

		Engine() = default;
		~Engine()
		{

		}



		void update(const float t_deltaTime)
		{
			for (const auto& pair : m_systems)
			{
				pair.second->update(t_deltaTime);
			}
		}

	private:

		std::unordered_map<id_t, ISystem*> m_systems;
	};
}