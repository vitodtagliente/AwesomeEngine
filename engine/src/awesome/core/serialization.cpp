#include "serialization.h"

#include <awesome/asset/asset_library.h>

template<>
json::value serialize(const IType& type)
{
	json::value data = json::object();
	for (const auto& [name, prop] : type.getTypeProperties())
	{
		if (!prop.isNormal) continue;

		switch (prop.type)
		{
		case PropertyType::T_bool: data[name] = prop.value<bool>(); break;
		case PropertyType::T_char: data[name] = prop.value<char>(); break;
		case PropertyType::T_double: data[name] = prop.value<double>(); break;
		case PropertyType::T_float: data[name] = prop.value<float>(); break;
		case PropertyType::T_int: data[name] = prop.value<int>(); break;
		case PropertyType::T_void: break;
		case PropertyType::T_container_string: data[name] = prop.value<std::string>(); break;
		case PropertyType::T_unknown:
		default:
		{
			if (prop.typeStr == "graphics::Color" || prop.typeStr == "Color")
			{
				data[name] = serialize(prop.value<graphics::Color>());
			}
			else if (prop.typeStr == "graphics::TextureCoords" || prop.typeStr == "TextureCoords")
			{
				data[name] = serialize(prop.value<graphics::TextureCoords>());
			}
			else if (prop.typeStr == "graphics::TextureRect" || prop.typeStr == "TextureRect")
			{
				data[name] = serialize(prop.value<graphics::TextureRect>());
			}
			else if (prop.typeStr == "math::transform" || prop.typeStr == "transform")
			{
				data[name] = serialize(prop.value<math::transform>());
			}
			else if (prop.typeStr == "math::vec4" || prop.typeStr == "vec4" || prop.typeStr == "math::vector4" || prop.typeStr == "vector4")
			{
				data[name] = serialize(prop.value<math::vec4>());
			}
			else if (prop.typeStr == "math::vec3" || prop.typeStr == "vec3" || prop.typeStr == "math::vector3" || prop.typeStr == "vector3")
			{
				data[name] = serialize(prop.value<math::vec3>());
			}
			else if (prop.typeStr == "math::vec2" || prop.typeStr == "vec2" || prop.typeStr == "math::vector2" || prop.typeStr == "vector2")
			{
				data[name] = serialize(prop.value<math::vec2>());
			}
			else if (prop.typeStr == "ImageAssetPtr")
			{
				data[name] = serialize(prop.value<ImageAssetPtr>());
			}
			else if (prop.typeStr == "PrefabAssetPtr")
			{
				data[name] = serialize(prop.value<PrefabAssetPtr>());
			}
			else if (prop.typeStr == "SceneAssetPtr")
			{
				data[name] = serialize(prop.value<SceneAssetPtr>());
			}
			else if (prop.typeStr == "SpriteAnimationAssetPtr")
			{
				data[name] = serialize(prop.value<SpriteAnimationAssetPtr>());
			}
			else if (prop.typeStr == "SpriteAssetPtr")
			{
				data[name] = serialize(prop.value<SpriteAssetPtr>());
			}
			else if (prop.typeStr == "TextAssetPtr")
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
	return static_cast<std::string>(asset->descriptor.id);
}

template<>
json::value serialize(const PrefabAssetPtr& asset)
{
	return static_cast<std::string>(asset->descriptor.id);
}

template<>
json::value serialize(const SceneAssetPtr& asset)
{
	return static_cast<std::string>(asset->descriptor.id);
}

template<>
json::value serialize(const SpriteAnimationAssetPtr& asset)
{
	return static_cast<std::string>(asset->descriptor.id);
}

template<>
json::value serialize(const SpriteAssetPtr& asset)
{
	return static_cast<std::string>(asset->descriptor.id);
}

template<>
json::value serialize(const TextAssetPtr& asset)
{
	return static_cast<std::string>(asset->descriptor.id);
}

template<>
bool deserialize(const json::value& value, IType& type)
{
	for (const auto& [name, prop] : type.getTypeProperties())
	{
		if (!prop.isNormal) continue;

		switch (prop.type)
		{
		case PropertyType::T_bool: prop.value<bool>() = value.safeAt(name).as_bool(false); break;
		case PropertyType::T_char: {
			const std::string str = value.safeAt(name).as_string("");
			if (str.length() == 1) {
				prop.value<char>() = str.at(0);
			}
			break;
		}
		case PropertyType::T_double: prop.value<double>() = value.safeAt(name).as_number(0).as_double(); break;
		case PropertyType::T_float: prop.value<double>() = value.safeAt(name).as_number(0).as_float(); break;
		case PropertyType::T_int: prop.value<int>() = value.safeAt(name).as_number(0).as_int(); break;
		case PropertyType::T_void: break;
		case PropertyType::T_container_string: prop.value<std::string>() = value.safeAt(name).as_string(""); break;
		case PropertyType::T_unknown:
		default:
		{
			if (prop.typeStr == "graphics::Color" || prop.typeStr == "Color")
			{
				deserialize(value.safeAt(name), prop.value<graphics::Color>());
			}
			else if (prop.typeStr == "graphics::TextureCoords" || prop.typeStr == "TextureCoords")
			{
				deserialize(value.safeAt(name), prop.value<graphics::TextureCoords>());
			}
			else if (prop.typeStr == "graphics::TextureRect" || prop.typeStr == "TextureRect")
			{
				deserialize(value.safeAt(name), prop.value<graphics::TextureRect>());
			}
			else if (prop.typeStr == "math::transform" || prop.typeStr == "transform")
			{
				deserialize(value.safeAt(name), prop.value<math::transform>());
			}
			else if (prop.typeStr == "math::vec4" || prop.typeStr == "vec4" || prop.typeStr == "math::vector4" || prop.typeStr == "vector4")
			{
				deserialize(value.safeAt(name), prop.value<math::vec4>());
			}
			else if (prop.typeStr == "math::vec3" || prop.typeStr == "vec3" || prop.typeStr == "math::vector3" || prop.typeStr == "vector3")
			{
				deserialize(value.safeAt(name), prop.value<math::vec3>());
			}
			else if (prop.typeStr == "math::vec2" || prop.typeStr == "vec2" || prop.typeStr == "math::vector2" || prop.typeStr == "vector2")
			{
				deserialize(value.safeAt(name), prop.value<math::vec2>());
			}
			else if (prop.typeStr == "ImageAssetPtr")
			{
				deserialize(value.safeAt(name), prop.value<ImageAssetPtr>());
			}
			else if (prop.typeStr == "PrefabAssetPtr")
			{
				deserialize(value.safeAt(name), prop.value<PrefabAssetPtr>());
			}
			else if (prop.typeStr == "SceneAssetPtr")
			{
				deserialize(value.safeAt(name), prop.value<SceneAssetPtr>());
			}
			else if (prop.typeStr == "SpriteAnimationAssetPtr")
			{
				deserialize(value.safeAt(name), prop.value<SpriteAnimationAssetPtr>());
			}
			else if (prop.typeStr == "SpriteAssetPtr")
			{
				deserialize(value.safeAt(name), prop.value<SpriteAssetPtr>());
			}
			else if (prop.typeStr == "TextAssetPtr")
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
