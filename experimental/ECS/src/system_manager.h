#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include "system.h"
#include "type_id.h"

namespace ECS
{
	template <typename T>
	constexpr unsigned int Foo()
	{
		return 0;
	}
	
	class SystemManager
	{
	public:

		SystemManager()
		{}
		~SystemManager() = default;

		template <typename T, typename... P>
		void add(P... t_args)
		{
			//assert(std::is_base_of<T, BaseSystem>());

			auto f = type_id<T>();

			constexpr id_t type_id = 1; // 
			const auto it = m_systems.find(type_id);
			// add if not found
			if (it == m_systems.end())
			{
				m_systems.insert({
					type_id,
					std::make_unique<T>(std::forward<P>(t_args)...)
					});
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