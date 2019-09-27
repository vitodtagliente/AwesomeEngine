#pragma once

#include <vector>
#include "entity.h"
#include "type_id.h"

namespace ECS
{
	class EntityManager
	{
	public:

		EntityManager()
			: m_idCounter()
			, m_entities()
			, m_reusableIds()
		{

		}

		~EntityManager() = default;

		id_t create()
		{
			const id_t new_entity = ++m_idCounter;
			m_entities.push_back(new_entity);
			return new_entity;
		}

		void destroy(const id_t t_id)
		{
			auto it = std::find(m_entities.begin(), m_entities.end(), t_id);
			if (it != m_entities.end())
			{
				m_entities.erase(it);
				m_reusableIds.push_back(t_id);
			}
		}

	private:

		// entitites id counter
		id_t m_idCounter;
		// entities list
		std::vector<id_t> m_entities;
		std::vector<id_t> m_reusableIds;

	};
}