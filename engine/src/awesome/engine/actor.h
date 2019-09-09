#pragma once

#include <memory>
#include <string>
#include <vector>
#include <awesome/core/string_id.h>
#include <awesome/math/transform.h>

namespace awesome
{
	class Component;

	class Actor
	{
	public:

		enum class State
		{
			Unknown,
			Normal,
			PendingDestroy
		};

		// get the id
		inline const StringId& getId() const { return m_id; }
		// get object state
		inline State getState() const { return m_state; }

		// object lifetime
		void initialize();
		// object update 
		void update(const double t_deltaTime);
		// destroy the object
		void destroy();

		// object name
		std::string name;
		// transform
		transform transform;
		// if true, this object cannot be moved
		bool isStatic;
		// if true this object is active
		bool active;

	protected:

		virtual void initialize_implementation() {}
		virtual void update_implementation(const float /*t_deltaTime*/) {}

	private:

		// actor id
		StringId m_id;
		// actor state
		State m_state;
		// parent actor
		std::weak_ptr<Actor> m_parent;
		// children actors
		std::vector<std::weak_ptr<Actor>> m_children;
		// actor components
		std::vector<std::unique_ptr<Component>> m_components;
	};
}