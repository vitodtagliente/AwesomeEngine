#include "component.h"

#include <awesome/scene/entity.h>

Component::Component(const Component& other)
	: enabled(other.enabled)
{

}

bool Component::operator==(const Component& other) const
{
	return m_id == other.m_id;
}

bool Component::operator!=(const Component& other) const
{
	return m_id != other.m_id;
}

const math::transform& Component::getOwnerTransform() const
{
	return m_owner->transform;
}

math::transform& Component::getOwnerTransform()
{
	return m_owner->transform;
}

void Component::queueOwnerDestroy()
{
	m_owner->queue_destroy();
}

void Component::attach(Entity* const entity)
{
	m_owner = entity;
}

void Component::detach()
{
	uninit();
	m_owner = nullptr;
}

void* Component::operator new(const std::size_t size)
{
	++s_metrics.count;
	s_metrics.size += size;
	return ::operator new(size);
}

void Component::operator delete(void* const ptr, const std::size_t size)
{
	--s_metrics.count;
	s_metrics.size -= size;
	return ::operator delete(ptr, size);
}