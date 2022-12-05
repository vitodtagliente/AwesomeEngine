/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/asset/prefab_asset.h>
#include <awesome/asset/scene_asset.h>
#include <awesome/asset/sprite_animation_asset.h>
#include <awesome/asset/sprite_asset.h>
#include <awesome/asset/text_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>
#include <awesome/encoding/json.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_coords.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/math/transform.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/math/vector4.h>

struct ISerializable
{
	virtual json::value serialize() const = 0;
	virtual void deserialize(const json::value& value) = 0;
};

struct Serializer
{
	static json::value serialize(const IType& type);
	static json::value serialize(const std::shared_ptr<IType>& type);
	static json::value serialize(const std::unique_ptr<IType>& type);
	static json::value serialize(const std::weak_ptr<IType>& type);
	static json::value serialize(const bool& primitive);
	static json::value serialize(const int& primitive);
	static json::value serialize(const float& primitive);
	static json::value serialize(const double& primitive);
	static json::value serialize(const char& primitive);
	static json::value serialize(const uuid& id);
	static json::value serialize(const graphics::Color& color);
	static json::value serialize(const graphics::TextureCoords& coords);
	static json::value serialize(const graphics::TextureRect& rect);
	static json::value serialize(const math::transform& t);
	static json::value serialize(const math::vec2& v);
	static json::value serialize(const math::vec3& v);
	static json::value serialize(const math::vec4& v);
	static json::value serialize(const ImageAssetPtr& asset);
	static json::value serialize(const PrefabAssetPtr& asset);
	static json::value serialize(const SceneAssetPtr& asset);
	static json::value serialize(const SpriteAnimationAssetPtr& asset);
	static json::value serialize(const SpriteAssetPtr& asset);
	static json::value serialize(const TextAssetPtr& asset);
	template <typename T>
	static json::value serialize(const std::vector<T>& list)
	{
		json::value data = json::array();
		for (const auto& element : list)
		{
			data.push_back(serialize(element));
		}
		return data;
	}
};

struct Deserializer
{
	static bool deserialize(const json::value& value, IType& type);
	static bool deserialize(const json::value& value, uuid& id);
	static bool deserialize(const json::value& value, graphics::Color& color);
	static bool deserialize(const json::value& value, graphics::TextureCoords& coords);
	static bool deserialize(const json::value& value, graphics::TextureRect& rect);
	static bool deserialize(const json::value& value, math::transform& t);
	static bool deserialize(const json::value& value, math::vec2& v);
	static bool deserialize(const json::value& value, math::vec3& v);
	static bool deserialize(const json::value& value, math::vec4& v);
	static bool deserialize(const json::value& value, ImageAssetPtr& asset);
	static bool deserialize(const json::value& value, PrefabAssetPtr& asset);
	static bool deserialize(const json::value& value, SceneAssetPtr& asset);
	static bool deserialize(const json::value& value, SpriteAnimationAssetPtr& asset);
	static bool deserialize(const json::value& value, SpriteAssetPtr& asset);
	static bool deserialize(const json::value& value, TextAssetPtr& asset);
};