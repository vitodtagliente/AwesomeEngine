#include "collider2d.h"

#include <awesome/editor/layout.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/renderer.h>
#include <awesome/entity/entity.h>

void Collider2d::render(graphics::Renderer* const renderer)
{
	switch (m_type)
	{
	case Type::Circle: renderer->getGizmos().circle(getOwner()->transform.position, m_circleSize, graphics::Color::Green); break;
	case Type::Rect: renderer->getGizmos().rect(getOwner()->transform.position, m_rectSize.x, m_rectSize.y, graphics::Color::Green); break;
	default: break;
	}
}

bool Collider2d::collide(Collider2d& other) const
{
	if (m_type == other.m_type)
	{
		const math::vec3 position = getOwner()->transform.position;
		const math::vec3 otherPosition = other.getOwner()->transform.position;

		if (m_type == Type::Rect)
		{
			const auto size1 = m_rectSize / 2;
			const auto size2 = other.m_rectSize / 2;

			return position.x + size1.x >= otherPosition.x - size2.x
				&& position.x - size1.x <= otherPosition.x + size2.x
				&& position.y + size1.y >= otherPosition.y - size2.y
				&& position.y - size1.y <= otherPosition.y + size2.y;
		}
		else // circle
		{
			return position.distance(otherPosition) <= m_circleSize + other.m_circleSize;
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
		return distance <= circleSize;
	}
}

json::value Collider2d::serialize() const
{
	json::value data = Component::serialize();
	data["type"] = enumToString(m_type);
	data["rectSize"] = ::serialize(m_rectSize);
	data["circleSize"] = m_circleSize;
	return data;
}

void Collider2d::deserialize(const json::value& value)
{
	Component::deserialize(value);
	stringToEnum(value["type"].as_string(), m_type);
	::deserialize(value["rectSize"], m_rectSize);
	m_circleSize = value["circleSize"].as_number().as_float();
}

void Collider2d::inspect()
{
	Component::inspect();
	editor::Layout::input("Type", m_type);
	switch (m_type)
	{
	case Type::Rect:
		editor::Layout::input("Size", m_rectSize);
		break;
	case Type::Circle:
		editor::Layout::input("Size", m_circleSize);
		break;
	default: break;
	}
}

REFLECT_COMPONENT(Collider2d)