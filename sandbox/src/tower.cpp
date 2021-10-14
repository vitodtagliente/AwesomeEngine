#include "tower.h"

#include <awesome/components/gizmos_renderer.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/gizmos.h>
#include <awesome/graphics/renderer.h>
#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>
#include <vdtmath/vector3.h>

#include "pojectile.h"

Tower::Tower()
	: Component()
	, m_finder(4.f, TargetFinder::Mode::Closer)
	, m_timer(1.0)
{
}

void Tower::init()
{
}

void Tower::update(double deltaTime)
{
	m_finder.check(*getWorld(), getOwner()->transform.position);
	m_timer.tick(deltaTime);

	if (m_timer.isExpired() && m_finder.hasTarget())
	{
		{
			Entity* const entity = getWorld()->spawn(getOwner()->transform.position, math::quaternion::identity);
			entity->name = std::string("projectile");
			entity->tag = "projectile";
			entity->transform.scale = math::vec3(0.2f, 0.2f, 1.f);
			if (Projectile* const projectile = entity->addComponent<Projectile>())
			{
				projectile->follow(m_finder.getTarget());
			}
			if (GizmosRenderer* component = entity->addComponent<GizmosRenderer>())
			{
				component->color = graphics::Color::Red;
				component->type = GizmosRenderer::Type::Circle;
			}
		}
		m_timer.reset();
	}
}

void Tower::render(graphics::Renderer* const renderer)
{
	const math::vec3& position = getOwner()->transform.position;
	renderer->getGizmos().circle(position, m_finder.getRadius(), graphics::Color::Yellow);
	if (m_finder.hasTarget())
	{
		renderer->getGizmos().line(position, m_finder.getTarget()->transform.position, graphics::Color::Red);
	}
}