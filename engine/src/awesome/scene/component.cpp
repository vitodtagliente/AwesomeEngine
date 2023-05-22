#include "component.h"

#include <awesome/scene/entity.h>
#include <awesome/core/logger.h>


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
	INFO_LOG("Component", THIS_FUNC + std::string("queueOwnerDestroy:") + std::to_string(m_owner->storageRef.getStorageId()));
	m_owner->queue_destroy();
}

Component* Component::attach(Entity* const entity)
{
	INFO_LOG("Component", THIS_FUNC + std::string("Component attached:") + std::to_string(entity->storageRef.getStorageId()));

	m_owner = entity;
	return this;
}

void Component::detach()
{
	INFO_LOG("Component", THIS_FUNC + std::string("Component detached:") + std::to_string(m_owner->storageRef.getStorageId()));

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