#include "object.h"
#include "component.h"

namespace awesome
{
	Object::Object()
		: name()
		, transform()
		, m_id()
		, m_children()
		, m_components()
	{
	}

	Object::~Object()
	{
	}

	Object* const Object::getChildById(const StringId& t_id) const
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

	Object* const Object::getChildByName(const StringId& t_name) const
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
		return getChildByName(StringId(t_name));
	}

	void Object::addChild(Object* const t_child)
	{
		m_children.push_back(t_child);
	}

	bool Object::removeChild(Object* const t_child)
	{
		for (auto it = m_children.begin(); it != m_children.end(); ++it)
		{
			if (*it == t_child)
			{
				m_children.erase(it);
				return true;
			}
		}
		return false;
	}

	Component* const Object::getComponentByName(const StringId& t_name) const
	{
		for (Component* const component : m_components)
		{
			if (component->getName() == t_name)
				return component;
		}
		return nullptr;
	}

	Component* const Object::getComponentByName(const std::string& t_name) const
	{
		return getComponentByName(StringId{ t_name });
	}

	void Object::initialize()
	{
		initialize_implementation();
	}

}