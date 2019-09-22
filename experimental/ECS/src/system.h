#pragma once 

#include <cassert>
#include <vector>
#include "data_component.h"
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
			, m_entityComponents()
		{
		}

		~System()
		{

		}

		inline const std::vector<T>& getComponents() const { return m_components; }

		template <typename... P>
		inline T& addComponent(const Entity::Id t_entityId, P... t_args)
		{
			static_assert(std::is_base_of<T, DataComponent>());

			m_components.push_back(T(std::forward<P>(t_args)...));
			return m_components.back();
		}

		void removeComponent(const Entity::Id t_entityId)
		{

		}

		inline void clear()
		{
			m_components.clear();
		}

		virtual void update(const float t_deltaTime) = 0;

	private:

		std::vector<T> m_components;
	};
}