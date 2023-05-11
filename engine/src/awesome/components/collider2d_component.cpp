#include "collider2d_component.h"

#include <awesome/collision/quad_tree.h>
#include <awesome/engine/engine.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/renderer.h>

bool intersect(const math::rect& rect, const math::circle& circle)
{
	// temporary variables to set edges for testing
	float testX = circle.x;
	float testY = circle.y;

	// which edge is closest?
	if (circle.x < rect.x - rect.width) testX = rect.x - rect.width;
	else if (circle.x > rect.x + rect.width) testX = rect.x + rect.width;
	if (circle.y < rect.y + rect.height) testY = rect.y + rect.height;
	else if (circle.y > rect.y - rect.height) testY = rect.y - rect.height;

	// get distance from closest edges
	float distX = circle.x - testX;
	float distY = circle.y - testY;
	float distance = ::sqrt((distX * distX) + (distY * distY));

	// if the distance is less than the radius, collision!
	return distance <= circle.radius;
}

Collider2dComponent::Collider2dComponent()
	: Component()
	, m_renderSettings(Engine::instance().settings.renderer)
{
}

void Collider2dComponent::init()
{
	s_components.push_back(this);

	update_aabb();
}

void Collider2dComponent::render(graphics::Renderer& renderer)
{
	if (m_renderSettings.debug && m_renderSettings.renderCollisions)
	{
		switch (m_type)
		{
		case Collision2DShapeType::Circle:
		{
			const math::circle& circle = std::get<math::circle>(m_aabb);
			renderer.submitDrawCircle(graphics::ShapeRenderStyle::stroke, math::vec3(circle.x, circle.y, 0.f), circle.radius, m_isColliding ? graphics::Color::Red : m_renderSettings.collisionWireColor);
			break;
		}
		case Collision2DShapeType::Rect:
		default:
		{
			const math::rect& rect = std::get<math::rect>(m_aabb);
			renderer.submitDrawRect(graphics::ShapeRenderStyle::stroke, math::vec3(rect.x, rect.y, 0.f), rect.width, rect.height, m_isColliding ? graphics::Color::Red : m_renderSettings.collisionWireColor);
			break;
		}
		}
	}
}

void Collider2dComponent::uninit()
{
	const auto& it = std::find(s_components.begin(), s_components.end(), this);
	if (it != s_components.end())
	{
		s_components.erase(it);
	}
}

void Collider2dComponent::update(const double)
{
	update_aabb();
	m_isColliding = false;

	const math::rect region = math::rect(getOwnerTransform().position.x, getOwnerTransform().position.y, bounds.x * 2, bounds.y * 2);
	for (const auto& entity : QuadTree::instance().query(region))
	{
		if (entity == getOwner()) continue;

		Collider2dComponent* const other = entity->findComponent<Collider2dComponent>();
		if (other)
		{
			collide(*other);
		}
	}
}

bool Collider2dComponent::collide(const Collider2dComponent& other)
{
	if (m_type == other.m_type)
	{
		if (m_type == Collision2DShapeType::Rect)
		{
			m_isColliding = std::get<math::rect>(m_aabb).intersects(std::get<math::rect>(other.m_aabb));
		}
		else // circle
		{
			m_isColliding = std::get<math::circle>(m_aabb).intersects(std::get<math::circle>(other.m_aabb));
		}
	}
	else
	{
		math::circle circle = m_type == Collision2DShapeType::Circle
			? std::get<math::circle>(m_aabb)
			: std::get<math::circle>(other.m_aabb);
		math::rect rect = m_type == Collision2DShapeType::Circle
			? std::get<math::rect>(m_aabb)
			: std::get<math::rect>(other.m_aabb);
		m_isColliding = intersect(rect, circle);
	}

	if (m_isColliding)
	{
		if (!isTrigger)
		{
			// onTrigger.broadcast(other);
		}
		else if (!other.isTrigger)
		{
			// onCollision.broadcast(other);
			return true;
		}
	}
	return false;
}

void Collider2dComponent::update_aabb()
{
	switch (m_type)
	{
	case Collision2DShapeType::Circle:
	{
		m_aabb = math::circle(getOwnerTransform().position.x, getOwnerTransform().position.y, bounds.x);
		break;
	}
	case Collision2DShapeType::Rect:
	default:
	{
		m_aabb = math::rect(getOwnerTransform().position.x, getOwnerTransform().position.y, bounds.x, bounds.y);
		break;
	}
	}
}
