#pragma once

#include <map>
#include <vector>
#include <unordered_map>
#include "entity_manager.h"
#include "system_manager.h"
#include "type_id.h"

namespace ECS
{
	class Engine
	{
	public:

		Engine()
			: m_entityManager()
			, m_systemManager()
		{ }

		~Engine() = default;

		void update(const float t_deltaTime)
		{
			m_systemManager.update(t_deltaTime);
		}

	private:

		EntityManager m_entityManager;
		SystemManager m_systemManager;
	};
}