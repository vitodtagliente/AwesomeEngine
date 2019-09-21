#pragma once 

#include <cassert>
#include <vector>
#include <unordered_map>
#include "entity.h"

namespace ECS
{
	class DataComponent;

	template <class T>
	class System
	{
	public:

		System()
			: m_components()
		{
		}

		~System()
		{

		}

		inline const std::vector<T>& getComponents() const { return m_components; }

		template <typename... P>
		inline T& addComponent(const Entity::id_t t_entityId, P... t_args)
		{
			static_assert(std::is_base_of<T, DataComponent>());

			m_components.push_back(T(std::forward<P>(t_args)...));
			return m_components.back();
		}

		inline void clear()
		{
			m_components.clear();
		}

	private:

		std::vector<T> m_components;
	};
}