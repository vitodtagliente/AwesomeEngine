#include "serialization.h"

#include <awesome/asset/asset_library.h>

template<>
json::value serialize(const IType& type)
{
	json::value data = json::object();
	for (const auto& [name, prop] : type.getTypeProperties())
	{
		if (prop.descriptor.decoratorType != Property::DecoratorType::D_normalized) continue;

		switch (prop.descriptor.type)
		{
		case Property::Type::T_bool: data[name] = prop.value<bool>(); break;
		case Property::Type::T_char: data[name] = prop.value<char>(); break;
		case Property::Type::T_custom_enum: data[name] = prop.value<int>(); break;
		case Property::Type::T_double: data[name] = prop.value<double>(); break;
		case Property::Type::T_float: data[name] = prop.value<float>(); break;
		case Property::Type::T_int: data[name] = prop.value<int>(); break;
		case Property::Type::T_void: break;
		case Property::Type::T_container_string: data[name] = prop.value<std::string>(); break;
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
json::value serialize(const ImageAssetPtr& asset)
{
	return static_cast<std::string>(asset != nullptr ? asset->descriptor.id : uuid::Invalid);
}

template<>
json::value serialize(const PrefabAssetPtr& asset)
{
	return static_cast<std::string>(asset != nullptr ? asset->descriptor.id : uuid::Invalid);
}

template<>
json::value serialize(const SceneAssetPtr& asset)
{
	return static_cast<std::string>(asset != nullptr ? asset->descriptor.id : uuid::Invalid);
}

template<>
json::value serialize(const SpriteAnimationAssetPtr& asset)
{
	return static_cast<std::string>(asset != nullptr ? asset->descriptor.id : uuid::Invalid);
}

template<>
json::value serialize(const SpriteAssetPtr& asset)
{
	return static_cast<std::string>(asset != nullptr ? asset->descriptor.id : uuid::Invalid);
}

template<>
json::value serialize(const TextAssetPtr& asset)
{
	return static_cast<std::string>(asset != nullptr ? asset->descriptor.id : uuid::Invalid);
}

template<>
bool deserialize(const json::value& value, IType& type)
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

template<>
bool deserialize(const json::value& value, ImageAssetPtr& asset)
{
	uuid id = uuid::Invalid;
	::deserialize(value, id);
	asset = AssetLibrary::instance().find<ImageAsset>(id);
	return true;
}

template<>
bool deserialize(const json::value& value, PrefabAssetPtr& asset)
{
	uuid id = uuid::Invalid;
	::deserialize(value, id);
	asset = AssetLibrary::instance().find<PrefabAsset>(id);
	return true;
}

template<>
bool deserialize(const json::value& value, SceneAssetPtr& asset)
{
	uuid id = uuid::Invalid;
	::deserialize(value, id);
	asset = AssetLibrary::instance().find<SceneAsset>(id);
	return true;
}

template<>
bool deserialize(const json::value& value, SpriteAnimationAssetPtr& asset)
{
	uuid id = uuid::Invalid;
	::deserialize(value, id);
	asset = AssetLibrary::instance().find<SpriteAnimationAsset>(id);
	return true;
}

template<>
bool deserialize(const json::value& value, SpriteAssetPtr& asset)
{
	uuid id = uuid::Invalid;
	::deserialize(value, id);
	asset = AssetLibrary::instance().find<SpriteAsset>(id);
	return true;
}

template<>
bool deserialize(const json::value& value, TextAssetPtr& asset)
{
	uuid id = uuid::Invalid;
	::deserialize(value, id);
	asset = AssetLibrary::instance().find<TextAsset>(id);
	return true;
}
