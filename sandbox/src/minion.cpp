#include "minion.h"

#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

#include "path.h"

Minion::Minion()
	: Component()
	, m_navigator()
	, m_speed(4.f)
{
}

void Minion::init()
{

}

void Minion::update(double deltaTime)
{
	if (m_navigator.isCompleted())
	{
		getWorld()->destroy(this->getOwner());
		return;
	}

	if (!m_navigator.isValid())
	{
		Path* const path = Path::findOrRandom(*getWorld(), "");
		if (path == nullptr) return;
		m_navigator.follow(path);
	}

	math::vec3 step;
	if (m_navigator.next(getOwner()->transform.position, step))
	{
		const math::vec3 direction = (step - getOwner()->transform.position).normalize();
		getOwner()->transform.position += direction * m_speed * deltaTime;
	}
}