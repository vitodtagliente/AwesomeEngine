#include "object.h"
#include "component.h"

namespace awesome
{
	Object::Object()
		: name()
		, transform()
		, isStatic(false)
		, active(true)
		, m_id()
		, m_children()
		, m_parent()
		, m_components()
		, m_state(State::Unknown)
	{
	}

	Object::~Object()
	{
		if (m_state == State::Normal)
		{
			destroy();
		}
	}

	Object* const Object::getChildById(const string_id& t_id) const
	{
		for (Object* const child : m_children)
		{
			if (child->getId() == t_id)
				return child;
		}
		return nullptr;
	}

	Object* const Object::getChildByIndex(unsigned int t_index) const
	{
		if (t_index < m_children.size())
			return m_children[t_index];
		return nullptr;
	}

	Object* const Object::getChildByName(const string_id& t_name) const
	{
		for (Object* const child : m_children)
		{
			if (child->name == t_name)
				return child;
		}
		return nullptr;
	}
	
	Object* const Object::getChildByName(const std::string& t_name) const
	{
		return getChildByName(string_id(t_name));
	}

	void Object::addChild(Object* const t_child)
	{
		m_children.push_back(t_child);
		t_child->m_parent = this;
	}

	bool Object::removeChild(Object* const t_child)
	{
		for (auto it = m_children.begin(); it != m_children.end(); ++it)
		{
			if (*it == t_child)
			{
				t_child->m_parent = nullptr;
				m_children.erase(it);
				return true;
			}
		}
		return false;
	}

	void Object::destroy()
	{
		for (Object* const child : m_children)
		{
			child->destroy();
		}

		if (!isRoot())
		{
			m_parent->removeChild(this);
		}

		for (Component* const component : m_components)
		{
			component->uninit();
			delete component;
		}

		m_state = State::PendingDestroy;
	}

	Component* const Object::getComponentByName(const string_id& t_name) const
	{
		for (Component* const component : m_components)
		{
			if (component->name == t_name)
				return component;
		}
		return nullptr;
	}

	Component* const Object::getComponentByName(const std::string& t_name) const
	{
		return getComponentByName(string_id{ t_name });
	}

	bool Object::removeComponent(Component* const t_component)
	{
		for (auto it = m_components.begin(); it != m_components.end(); ++it)
		{
			if (*it == t_component)
			{
				t_component->uninit();
				m_components.erase(it);
				delete t_component;
				return true;
			}
		}
		return false;
	}

	void Object::initialize()
	{
		initialize_implementation();
	}

	void Object::update(const double t_deltaTime)
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
			for (Component* const component : m_components)
			{
				if (component->enabled)
				{
					component->update(t_deltaTime);
				}
			}
			// specific implementation
			update_implementation(t_deltaTime);
		}
	}

}