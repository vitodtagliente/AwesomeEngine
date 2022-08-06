#include "vec3_serializer.h"

#include <awesome/math/vector3.h>

std::string Vec3Serializer::type()
{
	return "math::vec3";
}

json::value Vec3Serializer::serialize(const FieldDescriptor& field)
{
	const math::vec4& v = field.value<math::vec4>();
	return json::object({
		{"x", v.x},
		{"y", v.y},
		{"z", v.z}
		});
}

bool Vec3Serializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	if (!value.is_object())
		return false;

	math::vec4& v = field.value<math::vec4>();
	v.x = value.safeAt("x").as_number(0.0f).as_float();
	v.y = value.safeAt("y").as_number(0.0f).as_float();
	v.z = value.safeAt("z").as_number(0.0f).as_float();
	return true;
}
