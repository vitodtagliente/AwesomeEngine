#include "actor.h"

#include "component.h"

namespace awesome
{
	Actor::Actor()
	{
	}
	
	Actor::~Actor()
	{
		if (m_state != State::PendingDestroy)
		{
			destroy();
		}
	}
	
	void Actor::initialize()
	{
		initialize_implementation();
	}

	void Actor::update(const double t_deltaTime)
	{
		// update the transform if the object is not static
		if (!isStatic)
		{
			transform.update();
		}
		// if active update all the components
		if (active)
		{
			// update enabled components
			// for (Component* const component : m_components)
			// {
			// 	if (component->enabled)
			// 	{
			// 		component->update(t_deltaTime);
			// 	}
			// }
			// specific implementation
			update_implementation(t_deltaTime);
		}
	}

	void Actor::destroy()
	{
		// for (Object* const child : m_children)
		// {
		// 	child->destroy();
		// }

		// if (!isRoot())
		// {
		// 	m_parent->removeChild(this);
		// }

		// for (Component* const component : m_components)
		// {
		// 	component->uninit();
		// 	delete component;
		// }

		m_state = State::PendingDestroy;
	}
	
	void Actor::removeChild(const Actor* const t_child)
	{
		auto it = std::find(m_children.begin(), m_children.end(), t_child);
		if (it != m_children.end())
		{
			m_children.erase(it);
		}
	}
}