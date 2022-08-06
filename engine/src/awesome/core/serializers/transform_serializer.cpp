#include "transform_serializer.h"

#include <awesome/math/transform.h>

std::string TransformSerializer::type()
{
	return "math::transform";
}

json::value TransformSerializer::serialize(const FieldDescriptor& field)
{
	static const auto& serialize = [](const math::vec3& v) -> json::value
	{
		return json::object({
			{"x", v.x},
			{"y", v.y},
			{"z", v.z}
			});
	};

	const math::transform& transform = field.value<math::transform>();
	return json::object({
		{"position", serialize(transform.position)},
		{"rotation", serialize(transform.rotation)},
		{"scale", serialize(transform.scale)},
		{"isStatic", transform.isStatic}
		});
}

bool TransformSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	static const auto& deserialize = [](const json::value& value, math::vec3& v) -> bool
	{
		if (!value.is_object())
			return false;

		v.x = value.safeAt("x").as_number(0.0f).as_float();
		v.y = value.safeAt("y").as_number(0.0f).as_float();
		v.z = value.safeAt("z").as_number(0.0f).as_float();
		return true;
	};

	if (!value.is_object())
		return false;

	math::transform& transform = field.value<math::transform>();
	if (!deserialize(value.safeAt("position"), transform.position)) return false;
	if (!deserialize(value.safeAt("rotation"), transform.rotation)) return false;
	if (!deserialize(value.safeAt("scale"), transform.scale)) return false;
	transform.isStatic = value.safeAt("isStatic").as_bool(false);
	return true;
}
