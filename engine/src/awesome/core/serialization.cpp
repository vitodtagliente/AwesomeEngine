#include "serialization.h"

#include "serializers/color_serializer.h"
#include "serializers/uuid_serializer.h"

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

	color.red = value["r"].as_number(0.0f).as_float();
	color.green = value["g"].as_number(0.0f).as_float();
	color.blue = value["b"].as_number(0.0f).as_float();
	color.alpha = value["a"].as_number(0.0f).as_float();
	return true;
}

template<>
bool deserialize(const json::value& value, graphics::TextureCoords& coords)
{
	if (!value.is_object())
		return false;

	coords.u = value["u"].as_number(0.0f).as_float();
	coords.v = value["v"].as_number(0.0f).as_float();
	return true;
}

template<>
bool deserialize(const json::value& value, graphics::TextureRect& rect)
{
	if (!value.is_object())
		return false;

	rect.x = value["x"].as_number(0.0f).as_float();
	rect.y = value["y"].as_number(0.0f).as_float();
	rect.width = value["width"].as_number(0.0f).as_float();
	rect.height = value["height"].as_number(0.0f).as_float();
	return true;
}

template<>
bool deserialize(const json::value& value, math::transform& t)
{
	if (!value.is_object())
		return false;

	deserialize(value["position"], t.position);
	deserialize(value["rotation"], t.rotation);
	deserialize(value["scale"], t.scale);
	t.isStatic = value["isStatic"].as_bool(false);
	return true;
}

template<>
bool deserialize(const json::value& value, math::vec2& v)
{
	if (!value.is_object())
		return false;

	v.x = value["x"].as_number(0.0f).as_float();
	v.y = value["y"].as_number(0.0f).as_float();
	return true;
}

template<>
bool deserialize(const json::value& value, math::vec3& v)
{
	if (!value.is_object())
		return false;

	v.x = value["x"].as_number(0.0f).as_float();
	v.y = value["y"].as_number(0.0f).as_float();
	v.z = value["z"].as_number(0.0f).as_float();
	return true;
}

template<>
bool deserialize(const json::value& value, math::vec4& v)
{
	if (!value.is_object())
		return false;

	v.x = value["x"].as_number(0.0f).as_float();
	v.y = value["y"].as_number(0.0f).as_float();
	v.z = value["z"].as_number(0.0f).as_float();
	v.w = value["w"].as_number(0.0f).as_float();
	return true;
}

void Serializer::load()
{
	ColorSerializer::autoload();
	UuidSerializer::autoload();

	for (const std::string& name : TypeFactory::list("Category", "Serializer"))
	{
		IFieldSerializer* const serializer = TypeFactory::instantiate<IFieldSerializer>(name);
		if (serializer != nullptr)
		{
			m_serializers.insert(std::make_pair<std::string, FieldSerializerPtr>(serializer->type(), std::unique_ptr<IFieldSerializer>(serializer)));
		}
	}
}

json::value Serializer::serialize(IProtoClass* const proto) const
{
	if (proto == nullptr) return json::object();

	json::value data = json::object();
	data["proto_id"] = proto->get_descriptor().name;
	for (const auto& pair : proto->get_fields())
	{
		const FieldDescriptor& field = pair.second;
		switch (field.type)
		{
		case FieldDescriptor::Type::T_bool:
			data[pair.first] = field.value<bool>();
			break;
		case FieldDescriptor::Type::T_class:
			// data[pair.first] = field.value<bool>();
			break;
		case FieldDescriptor::Type::T_double:
			data[pair.first] = field.value<double>();
			break;
		case FieldDescriptor::Type::T_enum:
			data[pair.first] = field.value<int>();
			break;
		case FieldDescriptor::Type::T_float:
			data[pair.first] = field.value<float>();
			break;
		case FieldDescriptor::Type::T_int:
			data[pair.first] = field.value<int>();
			break;
		case FieldDescriptor::Type::T_map:
		{
			// data[pair.first] = field.value<bool>();
			break;
		}
		case FieldDescriptor::Type::T_string:
			data[pair.first] = field.value<std::string>();
			break;
		case FieldDescriptor::Type::T_unknown:

			break;
		case FieldDescriptor::Type::T_vector:
			// data[pair.first] = field.value<bool>();
			break;
		case FieldDescriptor::Type::T_void:	break;
		default: break;
		}
	}
	return data;
}

bool Serializer::deserialize(IProtoClass* const proto, const json::value& value) const
{
	return false;
}
