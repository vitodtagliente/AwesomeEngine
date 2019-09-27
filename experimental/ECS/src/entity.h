#pragma once

#include "component_ptr.h"
#include "entity_manager.h"
#include "system_manager.h"
#include "type_id.h"

namespace ECS
{
	class Entity
	{
	public:

		static constexpr size_t INVALID_ID = 0;
		
		Entity(EntityManager& t_manager, SystemManager& t_systems, const size_t t_id)
			: m_id(t_id)
			, m_manager(t_manager)
			, m_systems(t_systems)
		{  
			
		}

		virtual ~Entity() = default;

		size_t id() const { return m_id; }
		
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

		// component interface
		template <typename T, typename... P>
		void addComponent(P... t_args)
		{

		}

	private:
		// entity id
		size_t m_id;
		// entity manager reference
		EntityManager& m_manager;
		// system manager reference
		SystemManager& m_systems;
	};
}