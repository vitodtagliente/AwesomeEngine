#pragma once

namespace ECS
{
	class Entity
	{
	public:

		using id_t = size_t;

		Entity() = default;
		virtual ~Entity() = default;

		template <class T>
		T* getComponent() const
		{
			return nullptr; // todo
		}

		template <class T, class... A>
		T* addComponent(A&&... t_args)
		{
			return nullptr; // todo
		}

		template <class T>
		void removeComponent()
		{

		}

		virtual void enable() {}
		virtual void disable() {}
		
		inline bool operator== (const Entity& t_entity) const { return false; }
		inline bool operator!= (const Entity& t_entity) const { return false; }
	};
}