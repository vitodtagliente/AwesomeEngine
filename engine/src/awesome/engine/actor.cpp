#include "actor.h"

#include "component.h"

namespace awesome
{
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
}