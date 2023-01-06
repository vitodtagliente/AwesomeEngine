#include "serialization.h"

#include <awesome/asset/asset_library.h>
#include <awesome/core/string_util.h>

json::value Serializer::serialize(ISerializable* const serializable)
{
	if (serializable == nullptr)
		return json::value();

	return serializable->serialize();
}

json::value Serializer::serialize(const Type& type)
{
	json::value data = json::object();
	for (const auto& [name, prop] : type.getTypeProperties())
	{
		if (prop.descriptor.type == Property::Type::T_custom_type)
		{
			switch (prop.descriptor.decoratorType)
			{
			case Property::DecoratorType::D_shared_ptr: data[name] = serialize(prop.value<std::shared_ptr<Type>>()); break;
			case Property::DecoratorType::D_unique_ptr: data[name] = serialize(prop.value<std::unique_ptr<Type>>()); break;
			default:break;
			}
		}

		if (prop.descriptor.decoratorType != Property::DecoratorType::D_normalized) continue;

		switch (prop.descriptor.type)
		{
		case Property::Type::T_bool: data[name] = prop.value<bool>(); break;
		case Property::Type::T_char: data[name] = prop.value<char>(); break;
		case Property::Type::T_double: data[name] = prop.value<double>(); break;
		case Property::Type::T_float: data[name] = prop.value<float>(); break;
		case Property::Type::T_int: data[name] = prop.value<int>(); break;
		case Property::Type::T_void: break;
		case Property::Type::T_custom_enum: data[name] = prop.value<int>(); break;
		case Property::Type::T_custom_type:
		{

			break;
		}
		case Property::Type::T_container_string: data[name] = prop.value<std::string>(); break;
		case Property::Type::T_container_map:
		{
			if (prop.descriptor.children.front().type != Property::Type::T_container_string)
			{
				// string keys only are supported
				break;
			}

			switch (prop.descriptor.children.back().type)
			{
			case Property::Type::T_bool: data[name] = serialize(prop.value<std::map<std::string, bool>>()); break;
			case Property::Type::T_char: data[name] = serialize(prop.value<std::map<std::string, char>>()); break;
			case Property::Type::T_double: data[name] = serialize(prop.value<std::map<std::string, double>>()); break;
			case Property::Type::T_float: data[name] = serialize(prop.value<std::map<std::string, float>>()); break;
			case Property::Type::T_int: data[name] = serialize(prop.value<std::map<std::string, int>>()); break;
			case Property::Type::T_void: break;
			case Property::Type::T_custom_enum: data[name] = serialize(prop.value<std::map<std::string, int>>()); break;
			case Property::Type::T_custom_type:
			{
				switch (prop.descriptor.children.back().decoratorType)
				{
				case Property::DecoratorType::D_shared_ptr: data[name] = serialize(prop.value<std::map<std::string, std::shared_ptr<Type>>>()); break;
				case Property::DecoratorType::D_unique_ptr: data[name] = serialize(prop.value<std::map<std::string, std::unique_ptr<Type>>>()); break;
				default:break;
				}
				break;
			}
			case Property::Type::T_unknown:
			default:
			{
				const std::string& backChildTypeName = prop.descriptor.children.back().name;
				if (backChildTypeName == "graphics::Color" || backChildTypeName == "Color")
				{
					data[name] = serialize(prop.value<std::map<std::string, graphics::Color>>()); break;
				}
				else if (backChildTypeName == "graphics::TextureCoords" || backChildTypeName == "TextureCoords")
				{
					data[name] = serialize(prop.value<std::map<std::string, graphics::TextureCoords>>()); break;
				}
				else if (backChildTypeName == "graphics::TextureRect" || backChildTypeName == "TextureRect")
				{
					data[name] = serialize(prop.value<std::map<std::string, graphics::TextureRect>>()); break;
				}
				else if (backChildTypeName == "math::transform" || backChildTypeName == "transform")
				{
					data[name] = serialize(prop.value<std::map<std::string, math::transform>>()); break;
				}
				else if (backChildTypeName == "math::vec4" || backChildTypeName == "vec4" || backChildTypeName == "math::vector4" || backChildTypeName == "vector4")
				{
					data[name] = serialize(prop.value<std::map<std::string, math::vec4>>()); break;
				}
				else if (backChildTypeName == "math::vec3" || backChildTypeName == "vec3" || backChildTypeName == "math::vector3" || backChildTypeName == "vector3")
				{
					data[name] = serialize(prop.value<std::map<std::string, math::vec3>>()); break;
				}
				else if (backChildTypeName == "math::vec2" || backChildTypeName == "vec2" || backChildTypeName == "math::vector2" || backChildTypeName == "vector2")
				{
					data[name] = serialize(prop.value<std::map<std::string, math::vec2>>()); break;
				}
				else if (StringUtil::endsWith(backChildTypeName, "AssetPtr"))
				{
					data[name] = serialize(prop.value<std::map<std::string, AssetPtr>>()); break;
				}
				break;
			}
			}
			break;
		}
		case Property::Type::T_container_vector:
		{
			switch (prop.descriptor.children.front().type)
			{
			case Property::Type::T_bool: data[name] = serialize(prop.value<std::vector<bool>>()); break;
			case Property::Type::T_char: data[name] = serialize(prop.value<std::vector<char>>()); break;
			case Property::Type::T_double: data[name] = serialize(prop.value<std::vector<double>>()); break;
			case Property::Type::T_float: data[name] = serialize(prop.value<std::vector<float>>()); break;
			case Property::Type::T_int: data[name] = serialize(prop.value<std::vector<int>>()); break;
			case Property::Type::T_void: break;
			case Property::Type::T_custom_enum: data[name] = serialize(prop.value<std::vector<int>>()); break;
			case Property::Type::T_custom_type:
			{
				switch (prop.descriptor.children.front().decoratorType)
				{
				case Property::DecoratorType::D_shared_ptr: data[name] = serialize(prop.value<std::vector<std::shared_ptr<Type>>>()); break;
				case Property::DecoratorType::D_unique_ptr: data[name] = serialize(prop.value<std::vector<std::unique_ptr<Type>>>()); break;
				default:break;
				}
				break;
			}
			case Property::Type::T_unknown:
			default:
			{
				const std::string& frontChildTypeName = prop.descriptor.children.front().name;
				if (frontChildTypeName == "graphics::Color" || frontChildTypeName == "Color")
				{
					data[name] = serialize(prop.value<std::vector<graphics::Color>>()); break;
				}
				else if (frontChildTypeName == "graphics::TextureCoords" || frontChildTypeName == "TextureCoords")
				{
					data[name] = serialize(prop.value<std::vector<graphics::TextureCoords>>()); break;
				}
				else if (frontChildTypeName == "graphics::TextureRect" || frontChildTypeName == "TextureRect")
				{
					data[name] = serialize(prop.value<std::vector<graphics::TextureRect>>()); break;
				}
				else if (frontChildTypeName == "math::transform" || frontChildTypeName == "transform")
				{
					data[name] = serialize(prop.value<std::vector<math::transform>>()); break;
				}
				else if (frontChildTypeName == "math::vec4" || frontChildTypeName == "vec4" || frontChildTypeName == "math::vector4" || frontChildTypeName == "vector4")
				{
					data[name] = serialize(prop.value<std::vector<math::vec4>>()); break;
				}
				else if (frontChildTypeName == "math::vec3" || frontChildTypeName == "vec3" || frontChildTypeName == "math::vector3" || frontChildTypeName == "vector3")
				{
					data[name] = serialize(prop.value<std::vector<math::vec3>>()); break;
				}
				else if (frontChildTypeName == "math::vec2" || frontChildTypeName == "vec2" || frontChildTypeName == "math::vector2" || frontChildTypeName == "vector2")
				{
					data[name] = serialize(prop.value<std::vector<math::vec2>>()); break;
				}
				else if (StringUtil::endsWith(frontChildTypeName, "AssetPtr"))
				{
					data[name] = serialize(prop.value<std::vector<AssetPtr>>()); break;
				}
				break;
			}
			}
			break;
		}
		case Property::Type::T_unknown:
		default:
		{
			if (prop.descriptor.name == "graphics::Color" || prop.descriptor.name == "Color")
			{
				data[name] = serialize(prop.value<graphics::Color>());
			}
			else if (prop.descriptor.name == "graphics::TextureCoords" || prop.descriptor.name == "TextureCoords")
			{
				data[name] = serialize(prop.value<graphics::TextureCoords>());
			}
			else if (prop.descriptor.name == "graphics::TextureRect" || prop.descriptor.name == "TextureRect")
			{
				data[name] = serialize(prop.value<graphics::TextureRect>());
			}
			else if (prop.descriptor.name == "math::transform" || prop.descriptor.name == "transform")
			{
				data[name] = serialize(prop.value<math::transform>());
			}
			else if (prop.descriptor.name == "math::vec4" || prop.descriptor.name == "vec4" || prop.descriptor.name == "math::vector4" || prop.descriptor.name == "vector4")
			{
				data[name] = serialize(prop.value<math::vec4>());
			}
			else if (prop.descriptor.name == "math::vec3" || prop.descriptor.name == "vec3" || prop.descriptor.name == "math::vector3" || prop.descriptor.name == "vector3")
			{
				data[name] = serialize(prop.value<math::vec3>());
			}
			else if (prop.descriptor.name == "math::vec2" || prop.descriptor.name == "vec2" || prop.descriptor.name == "math::vector2" || prop.descriptor.name == "vector2")
			{
				data[name] = serialize(prop.value<math::vec2>());
			}
			else if (StringUtil::endsWith(prop.descriptor.name, "AssetPtr"))
			{
				data[name] = serialize(prop.value<AssetPtr>());
			}
			else if (StringUtil::startsWith(prop.descriptor.name, "TypeName"))
			{
				data[name] = serialize(prop.value<TypeName<Type>>());
			}
			break;
		}
		}
	}
	return data;
}

json::value Serializer::serialize(const std::shared_ptr<Type>& type)
{
	if (type != nullptr)
	{
		return serialize(*type.get());
	}
	return json::value();
}

json::value Serializer::serialize(const std::unique_ptr<Type>& type)
{
	if (type != nullptr)
	{
		return serialize(*type.get());
	}
	return json::value();
}

json::value Serializer::serialize(const bool& primitive)
{
	return json::value(primitive);
}

json::value Serializer::serialize(const int& primitive)
{
	return json::value(primitive);
}

json::value Serializer::serialize(const float& primitive)
{
	return json::value(primitive);
}

json::value Serializer::serialize(const double& primitive)
{
	return json::value(primitive);
}

json::value Serializer::serialize(const char& primitive)
{
	return json::value(primitive);
}

json::value Serializer::serialize(const std::string& primitive)
{
	return json::value(primitive);
}

json::value Serializer::serialize(const uuid& id)
{
	return json::value(static_cast<std::string>(id));
}

json::value Serializer::serialize(const graphics::Color& color)
{
	return json::object({
		{"r", color.red},
		{"g", color.green},
		{"b", color.blue},
		{"a", color.alpha}
		});
}

json::value Serializer::serialize(const graphics::TextureCoords& coords)
{
	return json::object({
		{"u", coords.u},
		{"v", coords.v}
		});
}

json::value Serializer::serialize(const graphics::TextureRect& rect)
{
	return json::object({
		{"x", rect.x},
		{"y", rect.y},
		{"width", rect.width},
		{"height", rect.height}
		});
}

json::value Serializer::serialize(const math::transform& t)
{
	return json::object({
		{"position", serialize(t.position)},
		{"rotation", serialize(t.rotation)},
		{"scale", serialize(t.scale)},
		{"isStatic", t.isStatic}
		});
}

json::value Serializer::serialize(const math::vec2& v)
{
	return json::object({
		{"x", v.x},
		{"y", v.y}
		});
}

json::value Serializer::serialize(const math::vec3& v)
{
	return json::object({
		{"x", v.x},
		{"y", v.y},
		{"z", v.z}
		});
}

json::value Serializer::serialize(const math::vec4& v)
{
	return json::object({
		{"x", v.x},
		{"y", v.y},
		{"z", v.z},
		{"w", v.w}
		});
}

json::value Serializer::serialize(const AssetPtr& asset)
{
	return static_cast<std::string>(asset != nullptr ? asset->descriptor.id : uuid::Invalid);
}

bool Deserializer::deserialize(const json::value& value, ISerializable* const serializable)
{
	if (serializable != nullptr)
	{
		serializable->deserialize(value);
		return true;
	}
	return false;
}

bool Deserializer::deserialize(const json::value& value, Type& type)
{
	for (const auto& [name, prop] : type.getTypeProperties())
	{
		if (prop.descriptor.type == Property::Type::T_custom_type)
		{
			switch (prop.descriptor.decoratorType)
			{
			case Property::DecoratorType::D_shared_ptr: deserialize(value.safeAt(name), prop.value<std::shared_ptr<Type>>(), prop.descriptor.name); break;
			case Property::DecoratorType::D_unique_ptr: deserialize(value.safeAt(name), prop.value<std::unique_ptr<Type>>(), prop.descriptor.name); break;
			default:break;
			}
		}

		if (prop.descriptor.decoratorType != Property::DecoratorType::D_normalized) continue;

		switch (prop.descriptor.type)
		{
		case Property::Type::T_bool: prop.value<bool>() = value.safeAt(name).as_bool(false); break;
		case Property::Type::T_char: {
			const std::string str = value.safeAt(name).as_string("");
			if (str.length() == 1) {
				prop.value<char>() = str.at(0);
			}
			break;
		}
		case Property::Type::T_double: prop.value<double>() = value.safeAt(name).as_number(0).as_double(); break;
		case Property::Type::T_float: prop.value<float>() = value.safeAt(name).as_number(0).as_float(); break;
		case Property::Type::T_int: prop.value<int>() = value.safeAt(name).as_number(0).as_int(); break;
		case Property::Type::T_void: break;
		case Property::Type::T_custom_enum: prop.value<int>() = value.safeAt(name).as_number(0).as_int(); break;
		case Property::Type::T_custom_type:
		{

			break;
		}
		case Property::Type::T_container_string: prop.value<std::string>() = value.safeAt(name).as_string(""); break;
		case Property::Type::T_container_map:
		{
			if (prop.descriptor.children.front().type != Property::Type::T_container_string)
			{
				// string keys only are supported
				break;
			}

			switch (prop.descriptor.children.back().type)
			{
			case Property::Type::T_bool: deserialize(value.safeAt(name), prop.value<std::map<std::string, bool>>()); break;
			case Property::Type::T_char: deserialize(value.safeAt(name), prop.value<std::map<std::string, char>>()); break;
			case Property::Type::T_double: deserialize(value.safeAt(name), prop.value<std::map<std::string, double>>()); break;
			case Property::Type::T_float: deserialize(value.safeAt(name), prop.value<std::map<std::string, float>>()); break;
			case Property::Type::T_int: deserialize(value.safeAt(name), prop.value<std::map<std::string, int>>()); break;
			case Property::Type::T_void: break;
			case Property::Type::T_custom_enum: deserialize(value.safeAt(name), prop.value<std::map<std::string, int>>()); break;
			case Property::Type::T_custom_type:
			{
				switch (prop.descriptor.children.back().decoratorType)
				{
				case Property::DecoratorType::D_shared_ptr: deserialize(value.safeAt(name), prop.value<std::map<std::string, std::shared_ptr<Type>>>(), prop.descriptor.children.back().name); break;
				case Property::DecoratorType::D_unique_ptr: deserialize(value.safeAt(name), prop.value<std::map<std::string, std::unique_ptr<Type>>>(), prop.descriptor.children.back().name); break;
				default:break;
				}
				break;
			}
			case Property::Type::T_unknown:
			default:
			{
				const std::string& backChildTypeName = prop.descriptor.children.back().name;
				if (backChildTypeName == "graphics::Color" || backChildTypeName == "Color")
				{
					deserialize(value.safeAt(name), prop.value<std::map<std::string, graphics::Color>>()); break;
				}
				else if (backChildTypeName == "graphics::TextureCoords" || backChildTypeName == "TextureCoords")
				{
					deserialize(value.safeAt(name), prop.value<std::map<std::string, graphics::TextureCoords>>()); break;
				}
				else if (backChildTypeName == "graphics::TextureRect" || backChildTypeName == "TextureRect")
				{
					deserialize(value.safeAt(name), prop.value<std::map<std::string, graphics::TextureRect>>()); break;
				}
				else if (backChildTypeName == "math::transform" || backChildTypeName == "transform")
				{
					deserialize(value.safeAt(name), prop.value<std::map<std::string, math::transform>>()); break;
				}
				else if (backChildTypeName == "math::vec4" || backChildTypeName == "vec4" || backChildTypeName == "math::vector4" || backChildTypeName == "vector4")
				{
					deserialize(value.safeAt(name), prop.value<std::map<std::string, math::vec4>>()); break;
				}
				else if (backChildTypeName == "math::vec3" || backChildTypeName == "vec3" || backChildTypeName == "math::vector3" || backChildTypeName == "vector3")
				{
					deserialize(value.safeAt(name), prop.value<std::map<std::string, math::vec3>>()); break;
				}
				else if (backChildTypeName == "math::vec2" || backChildTypeName == "vec2" || backChildTypeName == "math::vector2" || backChildTypeName == "vector2")
				{
					deserialize(value.safeAt(name), prop.value<std::map<std::string, math::vec2>>()); break;
				}
				else if (StringUtil::endsWith(backChildTypeName, "AssetPtr"))
				{
					deserialize(value.safeAt(name), prop.value<std::map<std::string, AssetPtr>>()); break;
				}
				break;
			}
			}
			break;
		}
		case Property::Type::T_container_vector:
		{
			switch (prop.descriptor.children.front().type)
			{
			case Property::Type::T_bool: deserialize(value.safeAt(name), prop.value<std::vector<bool>>()); break;
			case Property::Type::T_char: deserialize(value.safeAt(name), prop.value<std::vector<char>>()); break;
			case Property::Type::T_double: deserialize(value.safeAt(name), prop.value<std::vector<double>>()); break;
			case Property::Type::T_float: deserialize(value.safeAt(name), prop.value<std::vector<float>>()); break;
			case Property::Type::T_int: deserialize(value.safeAt(name), prop.value<std::vector<int>>()); break;
			case Property::Type::T_void: break;
			case Property::Type::T_custom_enum: deserialize(value.safeAt(name), prop.value<std::vector<int>>()); break;
			case Property::Type::T_custom_type:
			{
				switch (prop.descriptor.children.front().decoratorType)
				{
				case Property::DecoratorType::D_shared_ptr: deserialize(value.safeAt(name), prop.value<std::vector<std::shared_ptr<Type>>>(), prop.descriptor.children.front().name); break;
				case Property::DecoratorType::D_unique_ptr: deserialize(value.safeAt(name), prop.value<std::vector<std::unique_ptr<Type>>>(), prop.descriptor.children.front().name); break;
				default:break;
				}
				break;
			}
			case Property::Type::T_unknown:
			default:
			{
				const std::string& frontChildTypeName = prop.descriptor.children.front().name;
				if (frontChildTypeName == "graphics::Color" || frontChildTypeName == "Color")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<graphics::Color>>()); break;
				}
				else if (frontChildTypeName == "graphics::TextureCoords" || frontChildTypeName == "TextureCoords")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<graphics::TextureCoords>>()); break;
				}
				else if (frontChildTypeName == "graphics::TextureRect" || frontChildTypeName == "TextureRect")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<graphics::TextureRect>>()); break;
				}
				else if (frontChildTypeName == "math::transform" || frontChildTypeName == "transform")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<math::transform>>()); break;
				}
				else if (frontChildTypeName == "math::vec4" || frontChildTypeName == "vec4" || frontChildTypeName == "math::vector4" || frontChildTypeName == "vector4")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<math::vec4>>()); break;
				}
				else if (frontChildTypeName == "math::vec3" || frontChildTypeName == "vec3" || frontChildTypeName == "math::vector3" || frontChildTypeName == "vector3")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<math::vec3>>()); break;
				}
				else if (frontChildTypeName == "math::vec2" || frontChildTypeName == "vec2" || frontChildTypeName == "math::vector2" || frontChildTypeName == "vector2")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<math::vec2>>()); break;
				}
				else if (StringUtil::endsWith(frontChildTypeName, "AssetPtr"))
				{
					deserialize(value.safeAt(name), prop.value<std::vector<AssetPtr>>()); break;
				}
				break;
			}
			}
			break;
		}
		case Property::Type::T_unknown:
		default:
		{
			if (prop.descriptor.name == "graphics::Color" || prop.descriptor.name == "Color")
			{
				deserialize(value.safeAt(name), prop.value<graphics::Color>());
			}
			else if (prop.descriptor.name == "graphics::TextureCoords" || prop.descriptor.name == "TextureCoords")
			{
				deserialize(value.safeAt(name), prop.value<graphics::TextureCoords>());
			}
			else if (prop.descriptor.name == "graphics::TextureRect" || prop.descriptor.name == "TextureRect")
			{
				deserialize(value.safeAt(name), prop.value<graphics::TextureRect>());
			}
			else if (prop.descriptor.name == "math::transform" || prop.descriptor.name == "transform")
			{
				deserialize(value.safeAt(name), prop.value<math::transform>());
			}
			else if (prop.descriptor.name == "math::vec4" || prop.descriptor.name == "vec4" || prop.descriptor.name == "math::vector4" || prop.descriptor.name == "vector4")
			{
				deserialize(value.safeAt(name), prop.value<math::vec4>());
			}
			else if (prop.descriptor.name == "math::vec3" || prop.descriptor.name == "vec3" || prop.descriptor.name == "math::vector3" || prop.descriptor.name == "vector3")
			{
				deserialize(value.safeAt(name), prop.value<math::vec3>());
			}
			else if (prop.descriptor.name == "math::vec2" || prop.descriptor.name == "vec2" || prop.descriptor.name == "math::vector2" || prop.descriptor.name == "vector2")
			{
				deserialize(value.safeAt(name), prop.value<math::vec2>());
			}
			else if (StringUtil::endsWith(prop.descriptor.name, "AssetPtr"))
			{
				deserialize(value.safeAt(name), prop.value<AssetPtr>());
			}
			else if (StringUtil::startsWith(prop.descriptor.name, "TypeName"))
			{
				deserialize(value.safeAt(name), prop.value<TypeName<Type>>());
			}
			break;
		}
		}
	}
	return true;
}

bool Deserializer::deserialize(const json::value& value, std::shared_ptr<Type>& type)
{
	if (type == nullptr)
	{
		type = std::make_shared<Type>();
	}
	return deserialize(value, *type.get());
}

bool Deserializer::deserialize(const json::value& value, std::unique_ptr<Type>& type)
{
	if (type == nullptr)
	{
		type = std::make_unique<Type>();
	}
	return deserialize(value, *type.get());
}

bool Deserializer::deserialize(const json::value& value, std::shared_ptr<Type>& type, const std::string& typeName)
{
	if (type == nullptr)
	{
		type = std::shared_ptr<Type>(TypeFactory::instantiate(typeName));
	}
	return deserialize(value, *type.get());
}

bool Deserializer::deserialize(const json::value& value, std::unique_ptr<Type>& type, const std::string& typeName)
{
	if (type == nullptr)
	{
		type = std::unique_ptr<Type>(TypeFactory::instantiate(typeName));
	}
	return deserialize(value, *type.get());
}

bool Deserializer::deserialize(const json::value& value, bool& primitive)
{
	return primitive = value.as_bool(false), true;
}

bool Deserializer::deserialize(const json::value& value, int& primitive)
{
	return primitive = value.as_number(0).as_int(), true;
}

bool Deserializer::deserialize(const json::value& value, float& primitive)
{
	return primitive = value.as_number(0.f).as_float(), true;
}

bool Deserializer::deserialize(const json::value& value, double& primitive)
{
	return primitive = value.as_number(0).as_double(), true;
}

bool Deserializer::deserialize(const json::value& value, char& primitive)
{
	return primitive = value.as_string(" ").at(0), true;
}

bool Deserializer::deserialize(const json::value& value, std::string& primitive)
{
	return primitive = value.as_string(""), true;
}

bool Deserializer::deserialize(const json::value& value, uuid& id)
{
	id = uuid(value.as_string(static_cast<std::string>(uuid::Invalid)));
	return true;
}

bool Deserializer::deserialize(const json::value& value, graphics::Color& color)
{
	if (!value.is_object())
		return false;

	color.red = value.safeAt("r").as_number(0.0f).as_float();
	color.green = value.safeAt("g").as_number(0.0f).as_float();
	color.blue = value.safeAt("b").as_number(0.0f).as_float();
	color.alpha = value.safeAt("a").as_number(0.0f).as_float();
	return true;
}

bool Deserializer::deserialize(const json::value& value, graphics::TextureCoords& coords)
{
	if (!value.is_object())
		return false;

	coords.u = value.safeAt("u").as_number(0.0f).as_float();
	coords.v = value.safeAt("v").as_number(0.0f).as_float();
	return true;
}

bool Deserializer::deserialize(const json::value& value, graphics::TextureRect& rect)
{
	if (!value.is_object())
		return false;

	rect.x = value.safeAt("x").as_number(0.0f).as_float();
	rect.y = value.safeAt("y").as_number(0.0f).as_float();
	rect.width = value.safeAt("width").as_number(0.0f).as_float();
	rect.height = value.safeAt("height").as_number(0.0f).as_float();
	return true;
}

bool Deserializer::deserialize(const json::value& value, math::transform& t)
{
	if (!value.is_object())
		return false;

	deserialize(value.safeAt("position"), t.position);
	deserialize(value.safeAt("rotation"), t.rotation);
	deserialize(value.safeAt("scale"), t.scale);
	t.isStatic = value.safeAt("isStatic").as_bool(false);
	return true;
}

bool Deserializer::deserialize(const json::value& value, math::vec2& v)
{
	if (!value.is_object())
		return false;

	v.x = value.safeAt("x").as_number(0.0f).as_float();
	v.y = value.safeAt("y").as_number(0.0f).as_float();
	return true;
}

bool Deserializer::deserialize(const json::value& value, math::vec3& v)
{
	if (!value.is_object())
		return false;

	v.x = value.safeAt("x").as_number(0.0f).as_float();
	v.y = value.safeAt("y").as_number(0.0f).as_float();
	v.z = value.safeAt("z").as_number(0.0f).as_float();
	return true;
}

bool Deserializer::deserialize(const json::value& value, math::vec4& v)
{
	if (!value.is_object())
		return false;

	v.x = value.safeAt("x").as_number(0.0f).as_float();
	v.y = value.safeAt("y").as_number(0.0f).as_float();
	v.z = value.safeAt("z").as_number(0.0f).as_float();
	v.w = value.safeAt("w").as_number(0.0f).as_float();
	return true;
}

bool Deserializer::deserialize(const json::value& value, AssetPtr& asset)
{
	uuid id = uuid::Invalid;
	deserialize(value, id);
	asset = AssetLibrary::instance().find(id);
	return true;
}

bool Deserializer::deserialize(const json::value& value, std::vector<std::shared_ptr<Type>>& list, const std::string& typeName)
{
	return deserialize<std::shared_ptr<Type>>(
		value,
		list,
		[typeName]() -> std::shared_ptr<Type>
		{
			return std::shared_ptr<Type>(TypeFactory::instantiate(typeName));
		}
	);
}

bool Deserializer::deserialize(const json::value& value, std::vector<std::unique_ptr<Type>>& list, const std::string& typeName)
{
	return deserialize<std::unique_ptr<Type>>(
		value,
		list,
		[typeName]() -> std::unique_ptr<Type>
		{
			return std::unique_ptr<Type>(TypeFactory::instantiate(typeName));
		}
	);
}

bool Deserializer::deserialize(const json::value& value, std::map<std::string, std::shared_ptr<Type>>& map, const std::string& typeName)
{
	return deserialize<std::shared_ptr<Type>>(
		value,
		map,
		[typeName]() -> std::shared_ptr<Type>
		{
			return std::shared_ptr<Type>(TypeFactory::instantiate(typeName));
		}
	);
}

bool Deserializer::deserialize(const json::value& value, std::map<std::string, std::unique_ptr<Type>>& map, const std::string& typeName)
{
	return deserialize<std::unique_ptr<Type>>(
		value,
		map,
		[typeName]() -> std::unique_ptr<Type>
		{
			return std::unique_ptr<Type>(TypeFactory::instantiate(typeName));
		}
	);
}