#include "control.h"

Control::Control(const uuid& id)
	: m_id(id)
{
}

Control::Control(const Control& other)
{
	from_string(other.to_string());
}

Control& Control::operator=(const Control& other)
{
	from_string(other.to_string());
	return *this;
}

bool Control::operator==(const Control& other) const
{
	return m_id == other.m_id;
}

bool Control::operator!=(const Control& other) const
{
	return m_id != other.m_id;
}

void Control::queue_destroy()
{

}

void Control::update(const double deltaTime)
{
	
}

std::vector<Control*> Control::findChildrenByTag(const std::string& childTag) const
{
	std::vector<Control*> children;
	for (const auto& child : m_children)
	{
		if (child->tag == childTag)
		{
			children.push_back(child.get());
		}

		const auto& childChildren = child->findChildrenByTag(childTag);
		children.insert(children.end(), childChildren.begin(), childChildren.end());
	}
	return children;
}

Control* const Control::findChildById(const uuid& childId, const bool recursive) const
{
	for (const auto& child : m_children)
	{
		if (child->m_id == childId)
		{
			return child.get();
		}

		if (recursive)
		{
			Control* const Control = child->findChildById(childId, recursive);
			if (Control != nullptr) return Control;
		}
	}
	return nullptr;
}

Control* const Control::findChildByName(const std::string& childName) const
{
	for (const auto& child : m_children)
	{
		if (child->name == childName)
		{
			return child.get();
		}

		Control* const Control = child->findChildByName(childName);
		if (Control != nullptr) return Control;
	}
	return nullptr;
}

Control* const Control::findChildByTag(const std::string& childTag) const
{
	for (const auto& child : m_children)
	{
		if (child->tag == childTag)
		{
			return child.get();
		}

		Control* const Control = child->findChildByTag(childTag);
		if (Control != nullptr) return Control;
	}
	return nullptr;
}

Control* const Control::addChild()
{
	std::unique_ptr<Control> child = std::make_unique<Control>();
	child->m_parent = this;
	m_children.push_back(std::move(child));
	return m_children.back().get();
}

Control* const Control::addChild(std::unique_ptr<Control> Control)
{
	if (Control == nullptr) return nullptr;

	Control->m_parent = this;
	m_children.push_back(std::move(Control));
	return m_children.back().get();
}

bool Control::removeChild(Control* const Control)
{
	return removeChild(Control->m_id);
}

bool Control::removeChild(const uuid& id)
{
	for (auto it = m_children.begin(); it != m_children.end(); ++it)
	{
		const auto& child = *it;
		if (child->m_id == id)
		{
			return child->queue_destroy(), true;
		}

		if (child->removeChild(id))
		{
			return true;
		}
	}
	return false;
}

void Control::removeChildren()
{
	for (const auto& child : m_children)
	{
		child->queue_destroy();
	}
}