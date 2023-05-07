#include "collider2d_component.h"

#include <awesome/graphics/color.h>
#include <awesome/graphics/renderer.h>

void Collider2dComponent::render(graphics::Renderer& renderer)
{
	switch (m_type)
	{
	case Collision2DShapeType::Circle: renderer.submitDrawCircle(graphics::ShapeRenderStyle::stroke, getOwnerTransform().position, m_bounds.x, m_isColliding ? graphics::Color::Red : graphics::Color::Green); break;
	case Collision2DShapeType::Rect: renderer.submitDrawRect(graphics::ShapeRenderStyle::stroke, getOwnerTransform().position, m_bounds.x, m_bounds.y, m_isColliding ? graphics::Color::Red : graphics::Color::Green); break;
	default: break;
	}
	m_isColliding = false;
}

bool Collider2dComponent::collide(const Collider2dComponent& other)
{
	if (m_type == other.m_type)
	{
		math::vec3 position = getOwnerTransform().position;
		math::vec3 otherPosition = other.getOwnerTransform().position;
		position.z = otherPosition.z = 0.0f;

		if (m_type == Collision2DShapeType::Rect)
		{
			m_isColliding = position.x + m_bounds.x >= otherPosition.x - other.m_bounds.x
				&& position.x - m_bounds.x <= otherPosition.x + other.m_bounds.x
				&& position.y + m_bounds.y >= otherPosition.y - other.m_bounds.y
				&& position.y - m_bounds.y <= otherPosition.y + other.m_bounds.y;
		}
		else // circle
		{
			m_isColliding = position.distance(otherPosition) <= m_bounds.x + other.m_bounds.x;
		}
	}
	else
	{
		math::vec3 circlePosition, rectPosition;
		math::vec2 rectSize;
		float circleSize;
		if (m_type == Collision2DShapeType::Circle)
		{
			circlePosition = getOwnerTransform().position;
			circleSize = m_bounds.x;
			rectPosition = other.getOwnerTransform().position;
			rectSize = other.m_bounds;
		}
		else
		{
			circlePosition = other.getOwnerTransform().position;
			circleSize = other.m_bounds.x;
			rectPosition = getOwnerTransform().position;
			rectSize = m_bounds / 2;
		}

		math::vec3 test = rectPosition;

		if (circlePosition.x <= rectPosition.x - rectSize.x) test.x = rectPosition.x - rectSize.x;
		else if (circlePosition.x >= rectPosition.x + rectSize.x) test.x = rectPosition.x + rectSize.x;

		if (circlePosition.y >= rectPosition.y + rectSize.y) test.y = rectPosition.y + rectSize.y;
		else if (circlePosition.y <= rectPosition.y - rectSize.y) test.y = rectPosition.y - rectSize.y;

		const auto distance = circlePosition.distance(test);
		m_isColliding = distance <= circleSize;
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