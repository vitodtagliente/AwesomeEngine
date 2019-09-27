#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "system.h"
#include "type_id.h"

namespace ECS
{
	class SystemManager
	{
	public:

		SystemManager()
		{}
		~SystemManager() = default;

		template <typename T, typename... P>
		void add(P... t_args)
		{
			assert(std::is_base_of<T, BaseSystem>());

			const id_t type_id = type<T>.id();
			const auto it = m_systems.find(type_id);
			if (it != m_systems.end())
			{
				m_systems.insert(
					type<T>.id(),
					std::make_unique(std::forward<P>(t_args)...)
				);
			}			
		}

		void update(const float t_deltaTime)
		{
			for (const auto& pair : m_systems)
			{
				pair.second->update(t_deltaTime);
			}
		}

		void clear()
		{
			m_systems.clear();
		}

	private:

		std::unordered_map<id_t, std::unique_ptr<BaseSystem>> m_systems;
	};
}