#include "math_serializer.h"

#include <awesome/math/transform.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/math/vector4.h>

bool MathSerializer::canSerialize(const FieldDescriptor& field)
{
	return field.typeStr == "math::transform"
		|| field.typeStr == "math::vec2"
		|| field.typeStr == "math::vector2"
		|| field.typeStr == "math::vec3"
		|| field.typeStr == "math::vector3"
		|| field.typeStr == "math::vec4"
		|| field.typeStr == "math::vector4"
		;
}

json::value MathSerializer::serialize(const FieldDescriptor& field)
{
	static const auto& serialize = [](const math::vec3& v) -> json::value
	{
		return json::object({
			{"x", v.x},
			{"y", v.y},
			{"z", v.z}
			});
	};

	if (field.typeStr == "math::transform")
	{
		const math::transform& transform = field.value<math::transform>();
		return json::object({
			{"position", serialize(transform.position)},
			{"rotation", serialize(transform.rotation)},
			{"scale", serialize(transform.scale)},
			{"isStatic", transform.isStatic}
			});
	}
	else if (field.typeStr == "math::vec2" || field.typeStr == "math::vector2")
	{
		const math::vec2& v = field.value<math::vec2>();
		return json::object({
			{"x", v.x},
			{"y", v.y}
			});
	}
	else if (field.typeStr == "math::vec3" || field.typeStr == "math::vector3")
	{
		return serialize(field.value<math::vec3>());
	}
	else if (field.typeStr == "math::vec4" || field.typeStr == "math::vector4")
	{
		const math::vec4& v = field.value<math::vec4>();
		return json::object({
			{"x", v.x},
			{"y", v.y},
			{"z", v.z},
			{"w", v.w}
			});
	}
	return json::value();
}

bool MathSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	static const auto& deserialize = [](const json::value& value, math::vec3& v) -> void
	{
		v.x = value.safeAt("x").as_number(0.0f).as_float();
		v.y = value.safeAt("y").as_number(0.0f).as_float();
		v.z = value.safeAt("z").as_number(0.0f).as_float();
	};

	if (!value.is_object())
		return false;

	if (field.typeStr == "math::transform")
	{
		math::transform& transform = field.value<math::transform>();
		deserialize(value.safeAt("position"), transform.position);
		deserialize(value.safeAt("rotation"), transform.rotation);
		deserialize(value.safeAt("scale"), transform.scale);
		transform.isStatic = value.safeAt("isStatic").as_bool(false);
	}
	else if (field.typeStr == "math::vec2" || field.typeStr == "math::vector2")
	{
		math::vec2& v = field.value<math::vec2>();
		v.x = value.safeAt("x").as_number(0.0f).as_float();
		v.y = value.safeAt("y").as_number(0.0f).as_float();
	}
	else if (field.typeStr == "math::vec3" || field.typeStr == "math::vector3")
	{
		deserialize(value, field.value<math::vec3>());
	}
	else if (field.typeStr == "math::vec4" || field.typeStr == "math::vector4")
	{
		math::vec4& v = field.value<math::vec4>();
		v.x = value.safeAt("x").as_number(0.0f).as_float();
		v.y = value.safeAt("y").as_number(0.0f).as_float();
		v.z = value.safeAt("z").as_number(0.0f).as_float();
		v.w = value.safeAt("w").as_number(0.0f).as_float();
	}
	return true;
}
