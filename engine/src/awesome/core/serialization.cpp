#include "serialization.h"

template<>
json::value serialize(const IType& type)
{
	json::value data = json::object();
	for (const auto& [name, prop] : type.getTypeProperties())
	{
		if (!prop.isNormal) continue;

		switch (prop.type)
		{
		case PropertyType::T_bool: data[name] = prop.value<bool>(); break;
		case PropertyType::T_char: data[name] = prop.value<char>(); break;
		case PropertyType::T_double: data[name] = prop.value<double>(); break;
		case PropertyType::T_float: data[name] = prop.value<float>(); break;
		case PropertyType::T_int: data[name] = prop.value<int>(); break;
		case PropertyType::T_void: break;
		case PropertyType::T_container_string: data[name] = prop.value<std::string>(); break;
		case PropertyType::T_unknown: 
		default:
			break;
		}
	}
	return data;
}

template<>
json::value serialize(const uuid& id)
{
	return json::value(static_cast<std::string>(id));
}

template <>
json::value serialize(const graphics::Color& color)
{
	return json::object({
		{"r", color.red},
		{"g", color.green},
		{"b", color.blue},
		{"a", color.alpha}
		});
}

template <>
json::value serialize(const graphics::TextureCoords& coords)
{
	return json::object({
		{"u", coords.u},
		{"v", coords.v}
		});
}

template <>
json::value serialize(const graphics::TextureRect& rect)
{
	return json::object({
		{"x", rect.x},
		{"y", rect.y},
		{"width", rect.width},
		{"height", rect.height}
		});
}

template <>
json::value serialize(const math::transform& t)
{
	return json::object({
		{"position", serialize(t.position)},
		{"rotation", serialize(t.rotation)},
		{"scale", serialize(t.scale)},
		{"isStatic", t.isStatic}
		});
}

template <>
json::value serialize(const math::vec2& v)
{
	return json::object({
		{"x", v.x},
		{"y", v.y}
		});
}

template <>
json::value serialize(const math::vec3& v)
{
	return json::object({
		{"x", v.x},
		{"y", v.y},
		{"z", v.z}
		});
}

template <>
json::value serialize(const math::vec4& v)
{
	return json::object({
		{"x", v.x},
		{"y", v.y},
		{"z", v.z},
		{"w", v.w}
		});
}

template<>
bool deserialize(const json::value& value, uuid& id)
{
	id = uuid(value.as_string(static_cast<std::string>(uuid::Invalid)));
	return true;
}

template<>
bool deserialize(const json::value& value, graphics::Color& color)
{
	if (!value.is_object())
		return false;

	color.red = value.safeAt("r").as_number(0.0f).as_float();
	color.green = value.safeAt("g").as_number(0.0f).as_float();
	color.blue = value.safeAt("b").as_number(0.0f).as_float();
	color.alpha = value.safeAt("a").as_number(0.0f).as_float();
	return true;
}

template<>
bool deserialize(const json::value& value, graphics::TextureCoords& coords)
{
	if (!value.is_object())
		return false;

	coords.u = value.safeAt("u").as_number(0.0f).as_float();
	coords.v = value.safeAt("v").as_number(0.0f).as_float();
	return true;
}

template<>
bool deserialize(const json::value& value, graphics::TextureRect& rect)
{
	if (!value.is_object())
		return false;

	rect.x = value.safeAt("x").as_number(0.0f).as_float();
	rect.y = value.safeAt("y").as_number(0.0f).as_float();
	rect.width = value.safeAt("width").as_number(0.0f).as_float();
	rect.height = value.safeAt("height").as_number(0.0f).as_float();
	return true;
}

template<>
bool deserialize(const json::value& value, math::transform& t)
{
	if (!value.is_object())
		return false;

	deserialize(value.safeAt("position"), t.position);
	deserialize(value.safeAt("rotation"), t.rotation);
	deserialize(value.safeAt("scale"), t.scale);
	t.isStatic = value.safeAt("isStatic").as_bool(false);
	return true;
}

template<>
bool deserialize(const json::value& value, math::vec2& v)
{
	if (!value.is_object())
		return false;

	v.x = value.safeAt("x").as_number(0.0f).as_float();
	v.y = value.safeAt("y").as_number(0.0f).as_float();
	return true;
}

template<>
bool deserialize(const json::value& value, math::vec3& v)
{
	if (!value.is_object())
		return false;

	v.x = value.safeAt("x").as_number(0.0f).as_float();
	v.y = value.safeAt("y").as_number(0.0f).as_float();
	v.z = value.safeAt("z").as_number(0.0f).as_float();
	return true;
}

template<>
bool deserialize(const json::value& value, math::vec4& v)
{
	if (!value.is_object())
		return false;

	v.x = value.safeAt("x").as_number(0.0f).as_float();
	v.y = value.safeAt("y").as_number(0.0f).as_float();
	v.z = value.safeAt("z").as_number(0.0f).as_float();
	v.w = value.safeAt("w").as_number(0.0f).as_float();
	return true;
}