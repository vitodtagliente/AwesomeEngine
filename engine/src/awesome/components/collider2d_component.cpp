#include "collider2d_component.h"

#include <awesome/collision/quad_tree.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/renderer.h>

bool intersect(const math::rect& rect, const math::circle& circle)
{
	const math::circle c2(rect.x, rect.y, rect.width);
	return circle.intersects(c2);
}

Collider2DComponent::Collider2DComponent()
	: Component()
	, m_renderSettings(EngineSettings::instance().renderer)
{
}

void Collider2DComponent::init()
{
	update_aabb();
}

void Collider2DComponent::render(graphics::Renderer& renderer)
{
	if (m_renderSettings.debug && m_renderSettings.renderCollisions)
	{
		switch (m_type)
		{
		case ColliderType2D::Circle:
		{
			const math::circle& circle = std::get<math::circle>(m_aabb);
			renderer.submitDrawCircle(graphics::ShapeRenderStyle::stroke, math::vec3(circle.x, circle.y, 0.f), circle.radius, m_isColliding ? graphics::Color::Red : m_renderSettings.collisionWireColor);
			break;
		}
		case ColliderType2D::Rect:
		default:
		{
			const math::rect& rect = std::get<math::rect>(m_aabb);
			renderer.submitDrawRect(graphics::ShapeRenderStyle::stroke, math::vec3(rect.x, rect.y, 0.f), rect.width * 2, rect.height * 2, m_isColliding ? graphics::Color::Red : m_renderSettings.collisionWireColor);
			break;
		}
		}
	}
}

void Collider2DComponent::update(const double)
{
	update_aabb();
	m_isColliding = false;

	const math::rect region = math::rect(getOwnerTransform().position.x, getOwnerTransform().position.y, bounds.x * 2, bounds.y * 2);
	for (const auto& entity : QuadTree::instance().query(region))
	{
		if (entity == getOwner()) continue;

		Collider2DComponent* const other = entity->findComponent<Collider2DComponent>();
		if (other)
		{
			collide(*other);
		}
	}
}

bool Collider2DComponent::collide(const Collider2DComponent& other)
{
	if (m_type == other.m_type)
	{
		if (m_type == ColliderType2D::Rect)
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
		math::circle circle = m_type == ColliderType2D::Circle
			? std::get<math::circle>(m_aabb)
			: std::get<math::circle>(other.m_aabb);
		math::rect rect = m_type == ColliderType2D::Rect
			? std::get<math::rect>(m_aabb)
			: std::get<math::rect>(other.m_aabb);
		m_isColliding = intersect(rect, circle);
	}

	if (m_isColliding)
	{
		if (isTrigger)
		{
			onTrigger.invoke(other);
		}
		else
		{
			onCollision.invoke(other);
		}
		return true;
	}
	return false;
}

bool Collider2DComponent::collideAt(const math::vec3& futurePosition, const Collider2DComponent& other) const
{
	if (m_type == other.m_type)
	{
		if (m_type == ColliderType2D::Rect)
		{
			math::rect area = std::get<math::rect>(m_aabb);
			area.x = futurePosition.x;
			area.y = futurePosition.y;
			return area.intersects(std::get<math::rect>(other.m_aabb));
		}
		else // circle
		{
			math::circle area = std::get<math::circle>(m_aabb);
			area.x = futurePosition.x;
			area.y = futurePosition.y;
			return area.intersects(std::get<math::circle>(other.m_aabb));
		}
	}
	else
	{
		math::circle circle = m_type == ColliderType2D::Circle
			? std::get<math::circle>(m_aabb)
			: std::get<math::circle>(other.m_aabb);
		math::rect rect = m_type == ColliderType2D::Rect
			? std::get<math::rect>(m_aabb)
			: std::get<math::rect>(other.m_aabb);

		if (m_type == ColliderType2D::Rect)
		{
			rect.x = futurePosition.x;
			rect.y = futurePosition.y;
		}
		else
		{
			circle.x = futurePosition.x;
			circle.y = futurePosition.y;
		}
		return intersect(rect, circle);
	}
}

void Collider2DComponent::update_aabb()
{
	switch (m_type)
	{
	case ColliderType2D::Circle:
	{
		m_aabb = math::circle(getOwnerTransform().position.x, getOwnerTransform().position.y, bounds.x);
		break;
	}
	case ColliderType2D::Rect:
	default:
	{
		m_aabb = math::rect(getOwnerTransform().position.x, getOwnerTransform().position.y, bounds.x / 2, bounds.y / 2);
		break;
	}
	}
}
