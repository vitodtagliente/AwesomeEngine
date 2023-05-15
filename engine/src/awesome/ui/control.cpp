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

std::size_t Control::countChildren() const
{
	std::size_t size{ m_children.size() };
	for (const auto& child : m_children)
	{
		size += child->countChildren();
	}
	return size;
}

void Control::moveChild(Control* const parent, const uuid& childId)
{
	for (auto it = m_children.begin(); it != m_children.end(); ++it)
	{
		const auto& child = *it;
		if (child->m_id == childId)
		{
			parent->addChild(std::move(*it));
			m_children.erase(it);
			return;
		}
	}
}

void Control::queue_destroy()
{
	m_state = State::PendingDestroy;
	prepareToDestroy();
}

void Control::update(const double deltaTime)
{
	if (m_state == State::PendingSpawn)
	{
		prepareToSpawn();
	}
	if (m_state == State::PendingDestroy) return;

	m_children.erase(std::remove_if(
		m_children.begin(),
		m_children.end(),
		[](const std::unique_ptr<Control>& child) -> bool
		{
			return child->m_state == State::PendingDestroy;
		}
		),
		m_children.end()
	);

	for (auto it = m_behaviours.begin(); it != m_behaviours.end(); ++it)
	{
		const auto& behaviour = *it;
		if (behaviour->enabled)
		{
			behaviour->update(deltaTime);
		}
	}

	for (auto it = m_children.begin(); it != m_children.end(); ++it)
	{
		(*it)->update(deltaTime);
	}
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
			Control* const entity = child->findChildById(childId, recursive);
			if (entity != nullptr) return entity;
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

		Control* const entity = child->findChildByName(childName);
		if (entity != nullptr) return entity;
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

		Control* const entity = child->findChildByTag(childTag);
		if (entity != nullptr) return entity;
	}
	return nullptr;
}

Control* const Control::addChild()
{
	std::unique_ptr<Control> child = std::make_unique<Control>();
	child->m_parent = this;
	child->prepareToSpawn();
	m_children.push_back(std::move(child));
	return m_children.back().get();
}

Control* const Control::addChild(std::unique_ptr<Control> entity)
{
	if (entity == nullptr) return nullptr;

	entity->m_parent = this;
	entity->prepareToSpawn();
	m_children.push_back(std::move(entity));
	return m_children.back().get();
}

bool Control::removeChild(Control* const entity)
{
	return removeChild(entity->m_id);
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

void Control::removeBehaviour(ControlBehaviour* const behaviour)
{
	removeBehaviour(behaviour->getId());
}

void Control::removeBehaviour(const uuid& id)
{
	const auto& it = std::find_if(m_behaviours.begin(), m_behaviours.end(), [&id](const std::unique_ptr<ControlBehaviour>& behaviour) -> bool
		{
			return behaviour->getId() == id;
		}
	);

	if (it != m_behaviours.end())
	{
		const auto& behaviour = *it;
		behaviour->uninit();
		behaviour->detach();
		m_behaviours.erase(it);
	}
}

void Control::prepareToSpawn()
{
	for (const auto& behaviour : m_behaviours)
	{
		behaviour->attach(this);
		behaviour->init();
	}

	for (const auto& child : m_children)
	{
		child->prepareToSpawn();
	}

	m_state = State::Alive;
}

void Control::prepareToDestroy()
{
	for (const auto& child : m_children)
	{
		child->prepareToDestroy();
	}

	for (const auto& behaviour : m_behaviours)
	{
		behaviour->uninit();
	}
}