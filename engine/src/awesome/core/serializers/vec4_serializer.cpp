#include "vec4_serializer.h"

#include <awesome/math/vector4.h>

std::string Vec4Serializer::type()
{
	return "math::vec4";
}

json::value Vec4Serializer::serialize(const FieldDescriptor& field)
{
	const math::vec4& v = field.value<math::vec4>();
	return json::object({
		{"x", v.x},
		{"y", v.y},
		{"z", v.z},
		{"w", v.w}
		});
}

bool Vec4Serializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	if (!value.is_object())
		return false;

	math::vec4& v = field.value<math::vec4>();
	v.x = value.safeAt("x").as_number(0.0f).as_float();
	v.y = value.safeAt("y").as_number(0.0f).as_float();
	v.z = value.safeAt("z").as_number(0.0f).as_float();
	v.w = value.safeAt("w").as_number(0.0f).as_float();
	return true;
}
