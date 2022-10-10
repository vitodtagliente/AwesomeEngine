#include "collider2d_component.h"

#include <awesome/graphics/color.h>
#include <awesome/graphics/renderer.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

void Collider2dComponent::render(graphics::Renderer2D* const renderer)
{
	renderer->setPolygonStyle(graphics::PolygonStyle::stroke);
	switch (m_type)
	{
	case ShapeType::Circle: renderer->drawCircle(getOwner()->transform.position, m_circleSize, graphics::Color::Green); break;
	case ShapeType::Rect: renderer->drawRect(getOwner()->transform.position, m_rectSize.x, m_rectSize.y, graphics::Color::Green); break;
	default: break;
	}
	renderer->setPolygonStyle(graphics::PolygonStyle::fill);
}

bool Collider2dComponent::collide(const Collider2dComponent& other) const
{
	bool collision = false;

	if (m_type == other.m_type)
	{
		math::vec3 position = getOwner()->transform.position;
		math::vec3 otherPosition = other.getOwner()->transform.position;
		position.z = otherPosition.z = 0.0f;

		if (m_type == ShapeType::Rect)
		{
			const auto size1 = m_rectSize / 2;
			const auto size2 = other.m_rectSize / 2;

			collision = position.x + size1.x >= otherPosition.x - size2.x
				&& position.x - size1.x <= otherPosition.x + size2.x
				&& position.y + size1.y >= otherPosition.y - size2.y
				&& position.y - size1.y <= otherPosition.y + size2.y;
		}
		else // circle
		{
			collision = position.distance(otherPosition) <= m_circleSize + other.m_circleSize;
		}
	}
	else
	{
		math::vec3 circlePosition, rectPosition;
		math::vec2 rectSize;
		float circleSize;
		if (m_type == ShapeType::Circle)
		{
			circlePosition = getOwner()->transform.position;
			circleSize = m_circleSize;
			rectPosition = other.getOwner()->transform.position;
			rectSize = other.m_rectSize / 2;
		}
		else
		{
			circlePosition = other.getOwner()->transform.position;
			circleSize = other.m_circleSize;
			rectPosition = getOwner()->transform.position;
			rectSize = m_rectSize / 2;
		}

		math::vec3 test = rectPosition;

		if (circlePosition.x <= rectPosition.x - rectSize.x) test.x = rectPosition.x - rectSize.x;
		else if (circlePosition.x >= rectPosition.x + rectSize.x) test.x = rectPosition.x + rectSize.x;

		if (circlePosition.y >= rectPosition.y + rectSize.y) test.y = rectPosition.y + rectSize.y;
		else if (circlePosition.y <= rectPosition.y - rectSize.y) test.y = rectPosition.y - rectSize.y;

		const auto distance = circlePosition.distance(test);
		collision = distance <= circleSize;
	}

	if (collision)
	{
		if (!isTrigger && !other.isTrigger)
		{
			return true;
		}

		if (isTrigger)
		{
			onTrigger(other);
		}
		if (other.isTrigger)
		{
			other.onTrigger(*this);
		}
		return false;
	}
	return false;
}

void Collider2dComponent::inspect()
{
	Component::inspect();
	Layout::input("ShapeType", m_type);
}