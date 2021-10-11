#include "tower.h"

#include <awesome/editor/context.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/gizmos.h>
#include <awesome/graphics/renderer.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/world.h>
#include <vdtmath/vector3.h>

Tower::Tower()
	: Component()
	, m_finder(4.f, TargetFinder::Mode::Closer)
	, m_timer(1.0)
{
}

void Tower::init()
{
}

void Tower::update(World& world, double deltaTime)
{
	m_finder.check(world, getOwner()->transform.position);
	m_timer.tick(deltaTime);

	if (m_timer.isExpired() && m_finder.hasTarget())
	{
		// shoot
		m_timer.reset();
	}
}

void Tower::render(graphics::Renderer& renderer)
{
	const math::vec3& position = getOwner()->transform.position;
	renderer.getGizmos().circle(position, m_finder.getRadius(), graphics::Color::Yellow);
	if (m_finder.hasTarget())
	{
		renderer.getGizmos().line(position, m_finder.getTarget()->transform.position, graphics::Color::Red);
	}
}

void Tower::inspect(editor::Context& context)
{
	Component::inspect(context);

}
