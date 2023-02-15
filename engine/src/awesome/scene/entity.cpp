#include "entity.h"

Entity::Entity(const uuid& id)
	: m_id(id)
{
}

bool Entity::operator==(const Entity& other) const
{
	return m_id == other.m_id;
}

bool Entity::operator!=(const Entity& other) const
{
	return m_id != other.m_id;
}