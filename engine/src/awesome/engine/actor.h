#pragma once

#include <memory>
#include <string>
#include <vector>
#include <awesome/core/string_id.h>
#include <awesome/math/transform.h>
#include "component.h"

namespace awesome
{
	class Actor
	{
	public:

		Actor();
		virtual ~Actor();

		enum class State
		{
			Unknown,
			Normal,
			PendingDestroy
		};

		// get the id
		inline const string_id& getId() const { return m_id; }
		// get object state
		inline State getState() const { return m_state; }

		// object lifetime
		void initialize();
		// object update 
		void update(const double t_deltaTime);
		// destroy the object
		void destroy();

		// return the parent actor
		inline Actor* const getParent() const { return m_parent; }
		// get all children
		inline const std::vector<Actor*>& getChildren() const { return m_children; }
		// remove a child
		void removeChild(const Actor* const t_child);

		// check if this object is a leaf in scene tree
		inline bool isLeaf() const { return m_children.size() == 0; }
		// check if this object is root in scene tree
		inline bool isRoot() const { return m_parent != nullptr; }

		// get all the components 
		inline const std::vector<std::unique_ptr<Component>>& getComponents() const
		{
			return m_components;
		}
		// add a component of type
		template <typename T = Component>
		const std::unique_ptr<T>& addComponent()
		{
			m_components.push_back(std::move(std::make_unique<T>()));
			return m_components.back();
		}
		// #todo: getComponent, removeComponent

		bool operator== (const Actor& t_actor) const
		{
			return m_id == t_actor.m_id;
		}

		bool operator!= (const Actor& t_actor) const
		{
			return m_id != t_actor.m_id;
		}

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
		virtual void destroy_implementation() {}

	private:

		// actor id
		string_id m_id;
		// actor state
		State m_state;
		// parent actor
		Actor* m_parent;
		// children actors
		std::vector<Actor*> m_children;
		// actor components
		std::vector<std::unique_ptr<Component>> m_components;
	};
}