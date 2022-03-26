#include "serialization.h"

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
		{"scale", serialize(t.scale)}
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
bool deserialize(const json::value& value, graphics::Color& color)
{
	if (!value.is_object())
		return false;

	color.red = value["r"].as_number().as_float();
	color.green = value["g"].as_number().as_float();
	color.blue = value["b"].as_number().as_float();
	color.alpha = value["a"].as_number().as_float();
	return true;
}