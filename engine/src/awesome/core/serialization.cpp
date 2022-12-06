#include "serialization.h"

#include <awesome/asset/asset_library.h>

json::value Serializer::serialize(const Type& type)
{
	json::value data = json::object();
	for (const auto& [name, prop] : type.getTypeProperties())
	{
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
			// data[name] = ::serialize(prop.value<Type>());
			break;
		}
		case Property::Type::T_container_string: data[name] = prop.value<std::string>(); break;
		case Property::Type::T_container_map:
		{

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
				case Property::DecoratorType::D_shared_ptr: serialize(prop.value<std::vector<std::shared_ptr<Type>>>()); break;
				case Property::DecoratorType::D_unique_ptr: serialize(prop.value<std::vector<std::unique_ptr<Type>>>()); break;
				default:break;
				}
				break;
			}
			case Property::Type::T_unknown:
			default:
			{
				if (prop.descriptor.children.front().children.front().name == "graphics::Color" || prop.descriptor.children.front().children.front().name == "Color")
				{
					data[name] = serialize(prop.value<std::vector<graphics::Color>>()); break;
				}
				else if (prop.descriptor.children.front().name == "graphics::TextureCoords" || prop.descriptor.children.front().name == "TextureCoords")
				{
					data[name] = serialize(prop.value<std::vector<graphics::TextureCoords>>()); break;
				}
				else if (prop.descriptor.children.front().name == "graphics::TextureRect" || prop.descriptor.children.front().name == "TextureRect")
				{
					data[name] = serialize(prop.value<std::vector<graphics::TextureRect>>()); break;
				}
				else if (prop.descriptor.children.front().name == "math::transform" || prop.descriptor.children.front().name == "transform")
				{
					data[name] = serialize(prop.value<std::vector<math::transform>>()); break;
				}
				else if (prop.descriptor.children.front().name == "math::vec4" || prop.descriptor.children.front().name == "vec4" || prop.descriptor.children.front().name == "math::vector4" || prop.descriptor.children.front().name == "vector4")
				{
					data[name] = serialize(prop.value<std::vector<math::vec4>>()); break;
				}
				else if (prop.descriptor.children.front().name == "math::vec3" || prop.descriptor.children.front().name == "vec3" || prop.descriptor.children.front().name == "math::vector3" || prop.descriptor.children.front().name == "vector3")
				{
					data[name] = serialize(prop.value<std::vector<math::vec3>>()); break;
				}
				else if (prop.descriptor.children.front().name == "math::vec2" || prop.descriptor.children.front().name == "vec2" || prop.descriptor.children.front().name == "math::vector2" || prop.descriptor.children.front().name == "vector2")
				{
					data[name] = serialize(prop.value<std::vector<math::vec2>>()); break;
				}
				else if (prop.descriptor.children.front().name == "ImageAssetPtr")
				{
					data[name] = serialize(prop.value<std::vector<ImageAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "PrefabAssetPtr")
				{
					data[name] = serialize(prop.value<std::vector<PrefabAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "SceneAssetPtr")
				{
					data[name] = serialize(prop.value<std::vector<SceneAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "SpriteAnimationAssetPtr")
				{
					data[name] = serialize(prop.value<std::vector<SpriteAnimationAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "SpriteAssetPtr")
				{
					data[name] = serialize(prop.value<std::vector<SpriteAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "TextAssetPtr")
				{
					data[name] = serialize(prop.value<std::vector<TextAssetPtr>>()); break;
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
			else if (prop.descriptor.name == "ImageAssetPtr")
			{
				data[name] = serialize(prop.value<ImageAssetPtr>());
			}
			else if (prop.descriptor.name == "PrefabAssetPtr")
			{
				data[name] = serialize(prop.value<PrefabAssetPtr>());
			}
			else if (prop.descriptor.name == "SceneAssetPtr")
			{
				data[name] = serialize(prop.value<SceneAssetPtr>());
			}
			else if (prop.descriptor.name == "SpriteAnimationAssetPtr")
			{
				data[name] = serialize(prop.value<SpriteAnimationAssetPtr>());
			}
			else if (prop.descriptor.name == "SpriteAssetPtr")
			{
				data[name] = serialize(prop.value<SpriteAssetPtr>());
			}
			else if (prop.descriptor.name == "TextAssetPtr")
			{
				data[name] = serialize(prop.value<TextAssetPtr>());
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

json::value Serializer::serialize(const ImageAssetPtr& asset)
{
	return static_cast<std::string>(asset != nullptr ? asset->descriptor.id : uuid::Invalid);
}

json::value Serializer::serialize(const PrefabAssetPtr& asset)
{
	return static_cast<std::string>(asset != nullptr ? asset->descriptor.id : uuid::Invalid);
}

json::value Serializer::serialize(const SceneAssetPtr& asset)
{
	return static_cast<std::string>(asset != nullptr ? asset->descriptor.id : uuid::Invalid);
}

json::value Serializer::serialize(const SpriteAnimationAssetPtr& asset)
{
	return static_cast<std::string>(asset != nullptr ? asset->descriptor.id : uuid::Invalid);
}

json::value Serializer::serialize(const SpriteAssetPtr& asset)
{
	return static_cast<std::string>(asset != nullptr ? asset->descriptor.id : uuid::Invalid);
}

json::value Serializer::serialize(const TextAssetPtr& asset)
{
	return static_cast<std::string>(asset != nullptr ? asset->descriptor.id : uuid::Invalid);
}

bool Deserializer::deserialize(const json::value& value, Type& type)
{
	for (const auto& [name, prop] : type.getTypeProperties())
	{
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
		case Property::Type::T_custom_enum: prop.value<int>() = value.safeAt(name).as_number(0).as_int(); break;
		case Property::Type::T_double: prop.value<double>() = value.safeAt(name).as_number(0).as_double(); break;
		case Property::Type::T_float: prop.value<float>() = value.safeAt(name).as_number(0).as_float(); break;
		case Property::Type::T_int: prop.value<int>() = value.safeAt(name).as_number(0).as_int(); break;
		case Property::Type::T_void: break;
		case Property::Type::T_container_string: prop.value<std::string>() = value.safeAt(name).as_string(""); break;
		case Property::Type::T_container_map: 
		{
			break;
		}
		case Property::Type::T_container_vector:
		{
			/*
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
				// case Property::DecoratorType::D_shared_ptr: deserialize(value.safeAt(name), prop.value<std::vector<std::shared_ptr<Type>>>()); break;
				// case Property::DecoratorType::D_unique_ptr: deserialize(value.safeAt(name), prop.value<std::vector<std::unique_ptr<Type>>>()); break;
				default:break;
				}
				break;
			}
			case Property::Type::T_unknown:
			default:
			{
				if (prop.descriptor.children.front().children.front().name == "graphics::Color" || prop.descriptor.children.front().children.front().name == "Color")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<graphics::Color>>()); break;
				}
				else if (prop.descriptor.children.front().name == "graphics::TextureCoords" || prop.descriptor.children.front().name == "TextureCoords")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<graphics::TextureCoords>>()); break;
				}
				else if (prop.descriptor.children.front().name == "graphics::TextureRect" || prop.descriptor.children.front().name == "TextureRect")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<graphics::TextureRect>>()); break;
				}
				else if (prop.descriptor.children.front().name == "math::transform" || prop.descriptor.children.front().name == "transform")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<math::transform>>()); break;
				}
				else if (prop.descriptor.children.front().name == "math::vec4" || prop.descriptor.children.front().name == "vec4" || prop.descriptor.children.front().name == "math::vector4" || prop.descriptor.children.front().name == "vector4")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<math::vec4>>()); break;
				}
				else if (prop.descriptor.children.front().name == "math::vec3" || prop.descriptor.children.front().name == "vec3" || prop.descriptor.children.front().name == "math::vector3" || prop.descriptor.children.front().name == "vector3")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<math::vec3>>()); break;
				}
				else if (prop.descriptor.children.front().name == "math::vec2" || prop.descriptor.children.front().name == "vec2" || prop.descriptor.children.front().name == "math::vector2" || prop.descriptor.children.front().name == "vector2")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<math::vec2>>()); break;
				}
				else if (prop.descriptor.children.front().name == "ImageAssetPtr")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<ImageAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "PrefabAssetPtr")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<PrefabAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "SceneAssetPtr")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<SceneAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "SpriteAnimationAssetPtr")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<SpriteAnimationAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "SpriteAssetPtr")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<SpriteAssetPtr>>()); break;
				}
				else if (prop.descriptor.children.front().name == "TextAssetPtr")
				{
					deserialize(value.safeAt(name), prop.value<std::vector<TextAssetPtr>>()); break;
				}
				break;
			}
			}
			*/
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
			else if (prop.descriptor.name == "ImageAssetPtr")
			{
				deserialize(value.safeAt(name), prop.value<ImageAssetPtr>());
			}
			else if (prop.descriptor.name == "PrefabAssetPtr")
			{
				deserialize(value.safeAt(name), prop.value<PrefabAssetPtr>());
			}
			else if (prop.descriptor.name == "SceneAssetPtr")
			{
				deserialize(value.safeAt(name), prop.value<SceneAssetPtr>());
			}
			else if (prop.descriptor.name == "SpriteAnimationAssetPtr")
			{
				deserialize(value.safeAt(name), prop.value<SpriteAnimationAssetPtr>());
			}
			else if (prop.descriptor.name == "SpriteAssetPtr")
			{
				deserialize(value.safeAt(name), prop.value<SpriteAssetPtr>());
			}
			else if (prop.descriptor.name == "TextAssetPtr")
			{
				deserialize(value.safeAt(name), prop.value<TextAssetPtr>());
			}
			break;
		}
		}
	}
	return true;
}

bool Deserializer::deserialize(const json::value& value, std::shared_ptr<Type>& type)
{
	type = std::make_shared<Type>();
	return deserialize(value, *type.get());
}

bool Deserializer::deserialize(const json::value& value, std::unique_ptr<Type>& type)
{
	type = std::make_unique<Type>();
	return deserialize(value, *type.get());
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

bool Deserializer::deserialize(const json::value& value, ImageAssetPtr& asset)
{
	uuid id = uuid::Invalid;
	deserialize(value, id);
	asset = AssetLibrary::instance().find<ImageAsset>(id);
	return true;
}

bool Deserializer::deserialize(const json::value& value, PrefabAssetPtr& asset)
{
	uuid id = uuid::Invalid;
	deserialize(value, id);
	asset = AssetLibrary::instance().find<PrefabAsset>(id);
	return true;
}

bool Deserializer::deserialize(const json::value& value, SceneAssetPtr& asset)
{
	uuid id = uuid::Invalid;
	deserialize(value, id);
	asset = AssetLibrary::instance().find<SceneAsset>(id);
	return true;
}

bool Deserializer::deserialize(const json::value& value, SpriteAnimationAssetPtr& asset)
{
	uuid id = uuid::Invalid;
	deserialize(value, id);
	asset = AssetLibrary::instance().find<SpriteAnimationAsset>(id);
	return true;
}

bool Deserializer::deserialize(const json::value& value, SpriteAssetPtr& asset)
{
	uuid id = uuid::Invalid;
	deserialize(value, id);
	asset = AssetLibrary::instance().find<SpriteAsset>(id);
	return true;
}

bool Deserializer::deserialize(const json::value& value, TextAssetPtr& asset)
{
	uuid id = uuid::Invalid;
	deserialize(value, id);
	asset = AssetLibrary::instance().find<TextAsset>(id);
	return true;
}
