#pragma once

#include "entity_manager.h"
#include "type_id.h"

namespace ECS
{
	class Entity
	{
	public:

		static constexpr id_t INVALID_ID = 0;
		
		Entity(EntityManager& t_manager, const id_t t_id)
			: m_id(t_id)
			, m_manager(t_manager)
		{  
			
		}

		virtual ~Entity() = default;

		id_t id() const { return m_id; }
		
		operator bool() const
		{
			return valid();
		}

		bool valid() const
		{
			return m_id != INVALID_ID;
		}

		void invalidate()
		{
			m_manager.destroy(m_id);
			m_id = INVALID_ID;
		}

		inline virtual bool operator== (const Entity& t_other) const
		{ 
			return m_id == t_other.m_id; 
		}
		inline virtual bool operator!= (const Entity& t_other) const
		{ 
			return m_id != t_other.m_id; 
		}

	private:
		// entity id
		id_t m_id;
		// entity manager reference
		EntityManager& m_manager;
	};
}