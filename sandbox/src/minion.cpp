#include "minion.h"

#include <awesome/editor/context.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/world.h>

#include "path.h"

Minion::Minion()
	: Component()
	, m_navigator()
	, m_speed(5.f)
{
}

void Minion::init()
{

}

void Minion::update(World& world, double deltaTime)
{
	if (m_navigator.isCompleted())
	{
		world.destroy(this->getOwner());
		return;
	}

	if (!m_navigator.isValid())
	{
		Path* const path = Path::findOrRandom(world, "");
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

void Minion::inspect(editor::Context& context)
{
	Component::inspect(context);
	context.input("speed", &m_speed);
}