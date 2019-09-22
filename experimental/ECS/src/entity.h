#pragma once

namespace ECS
{
	class Entity
	{
	public:

		using Id = size_t;

		Entity()
			: m_id(++id_counter)
		{

		}
		virtual ~Entity() = default;

		Id id() const { return m_id; }

		template <typename T, typename... P>
		void addComponent(P... t_args)
		{
			
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

		static Id id_counter;

		// entity id
		Id m_id;
	};

	Entity::Id Entity::id_counter = 0;
}