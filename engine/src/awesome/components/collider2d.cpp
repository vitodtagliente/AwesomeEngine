#include "collider2d.h"

#include <awesome/editor/layout.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/renderer.h>
#include <awesome/entity/entity.h>

void Collider2D::render(graphics::Renderer* const renderer)
{
	switch (m_type)
	{
	case Type::Box: renderer->getGizmos().rect(getOwner()->transform.position, m_boxSize.x, m_boxSize.y, graphics::Color::Green); break;
	case Type::Circle: renderer->getGizmos().circle(getOwner()->transform.position, m_circleSize, graphics::Color::Green); break;
	default: break;
	}
}

bool Collider2D::collide(Collider2D& other) const
{
	if (m_type == other.m_type)
	{
		return true;
	}
	else
	{
		return false;
	}
}

json::value Collider2D::serialize() const
{
	json::value data = Component::serialize();
	data["type"] = enumToString(m_type);
	data["boxSize"] = ::serialize(m_boxSize);
	data["circleSize"] = m_circleSize;
	return data;
}

void Collider2D::deserialize(const json::value& value)
{
	Component::deserialize(value);
	stringToEnum(value["type"].as_string(), m_type);
	::deserialize(value["boxSize"], m_boxSize);
	m_circleSize = value["circleSize"].as_number().as_float();
}

void Collider2D::inspect()
{
	Component::inspect();
	editor::Layout::input("Type", m_type);
	switch (m_type)
	{
	case Type::Box:
		editor::Layout::input("Size", m_boxSize);
		break;
	case Type::Circle:
		editor::Layout::input("Size", m_circleSize);
		break;
	default: break;
	}
}

REFLECT_COMPONENT(Collider2D)