#include "component.h"

#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

bool Component::operator==(const Component& other) const
{
	return m_id == other.m_id;
}

bool Component::operator!=(const Component& other) const
{
	return m_id != other.m_id;
}

void Component::attach(Entity* const entity)
{
	m_owner = entity;
}

void Component::detach()
{
	uninit();
	m_owner = nullptr;
}

json::value Component::serialize() const
{
	json::value data = ::serialize((const IType&)*this);
	data["component_type"] = this->getTypeName();
	return data;
}

void Component::deserialize(const json::value& value)
{	
	::deserialize(value.safeAt("id"), (const IType&)*this);
}

void Component::inspect()
{
	for (const auto& [name, prop] : this->getTypeProperties())
	{
		if (!prop.isNormal) continue;

		switch (prop.type)
		{
		case PropertyType::T_bool: Layout::input(name, prop.value<bool>()); break;
		case PropertyType::T_char: break;
		case PropertyType::T_double: Layout::input(name, prop.value<double>()); break;
		case PropertyType::T_float: Layout::input(name, prop.value<float>()); break;
		case PropertyType::T_int: Layout::input(name, prop.value<int>()); break;
		case PropertyType::T_void: break;
		case PropertyType::T_container_string: Layout::input(name, prop.value<std::string>()); break;
		case PropertyType::T_unknown:
		default:
		{
			if (prop.typeStr == "graphics::Color" || prop.typeStr == "Color")
			{
				Layout::input(name, prop.value<graphics::Color>());
			}
			else if (prop.typeStr == "graphics::TextureCoords" || prop.typeStr == "TextureCoords")
			{
				Layout::input(name, prop.value<graphics::TextureCoords>());
			}
			else if (prop.typeStr == "graphics::TextureRect" || prop.typeStr == "TextureRect")
			{
				Layout::input(name, prop.value<graphics::TextureRect>());
			}
			else if (prop.typeStr == "math::transform" || prop.typeStr == "transform")
			{
				Layout::input("Position", prop.value<math::transform>().position);
				Layout::input("Rotation", prop.value<math::transform>().rotation);
				Layout::input("Scale", prop.value<math::transform>().scale);
				Layout::input("Static", prop.value<math::transform>().isStatic);
			}
			else if (prop.typeStr == "math::vec4" || prop.typeStr == "vec4" || prop.typeStr == "math::vector4" || prop.typeStr == "vector4")
			{
				Layout::input(name, prop.value<math::vec4>());
			}
			else if (prop.typeStr == "math::vec3" || prop.typeStr == "vec3" || prop.typeStr == "math::vector3" || prop.typeStr == "vector3")
			{
				Layout::input(name, prop.value<math::vec3>());
			}
			else if (prop.typeStr == "math::vec2" || prop.typeStr == "vec2" || prop.typeStr == "math::vector2" || prop.typeStr == "vector2")
			{
				Layout::input(name, prop.value<math::vec2>());
			}
			break;
		}
		}
	}
}