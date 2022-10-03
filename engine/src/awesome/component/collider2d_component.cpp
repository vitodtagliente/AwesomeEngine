#include "collider2d_component.h"

#include <awesome/editor/layout.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/renderer.h>
#include <awesome/entity/entity.h>

void Collider2dComponent::render(graphics::Renderer2D* const renderer)
{
	renderer->setPolygonStyle(graphics::PolygonStyle::stroke);
	switch (m_type)
	{
	case Type::Circle: renderer->drawCircle(getOwner()->transform.position, m_circleSize, graphics::Color::Green); break;
	case Type::Rect: renderer->drawRect(getOwner()->transform.position, m_rectSize.x, m_rectSize.y, graphics::Color::Green); break;
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

		if (m_type == Type::Rect)
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
		if (m_type == Type::Circle)
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

json::value Collider2dComponent::serialize() const
{
	json::value data = Component::serialize();
	data["type"] = enumToString(m_type);
	data["rectSize"] = ::serialize(m_rectSize);
	data["circleSize"] = m_circleSize;
	data["isTrigger"] = isTrigger;
	return data;
}

void Collider2dComponent::deserialize(const json::value& value)
{
	Component::deserialize(value);
	stringToEnum(value.safeAt("type").as_string(""), m_type);
	::deserialize(value.safeAt("rectSize"), m_rectSize);
	m_circleSize = value.safeAt("circleSize").as_number(1.f).as_float();
	isTrigger = value.safeAt("isTrigger").as_bool(false);
}

void Collider2dComponent::inspect()
{
	Component::inspect();
	Layout::input("Type", m_type);
	switch (m_type)
	{
	case Type::Rect:
		Layout::input("Size", m_rectSize);
		break;
	case Type::Circle:
		Layout::input("Size", m_circleSize);
		break;
	default: break;
	}
	Layout::input("Is Trigger", isTrigger);
}