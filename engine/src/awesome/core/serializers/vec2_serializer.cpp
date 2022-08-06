#include "vec2_serializer.h"

#include <awesome/math/vector2.h>

std::string Vec2Serializer::type()
{
	return "math::vec2";
}

json::value Vec2Serializer::serialize(const FieldDescriptor& field)
{
	const math::vec4& v = field.value<math::vec4>();
	return json::object({
		{"x", v.x},
		{"y", v.y}
		});
}

bool Vec2Serializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	if (!value.is_object())
		return false;

	math::vec4& v = field.value<math::vec4>();
	v.x = value.safeAt("x").as_number(0.0f).as_float();
	v.y = value.safeAt("y").as_number(0.0f).as_float();
	return true;
}
