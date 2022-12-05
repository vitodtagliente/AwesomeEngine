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
	json::value serialize(const IType& type);
	json::value serialize(const std::shared_ptr<IType>& type);
	json::value serialize(const std::unique_ptr<IType>& type);
	json::value serialize(const std::weak_ptr<IType>& type);
	json::value serialize(const bool& primitive);
	json::value serialize(const int& primitive);
	json::value serialize(const float& primitive);
	json::value serialize(const double& primitive);
	json::value serialize(const char& primitive);
	json::value serialize(const uuid& id);
	json::value serialize(const graphics::Color& color);
	json::value serialize(const graphics::TextureCoords& coords);
	json::value serialize(const graphics::TextureRect& rect);
	json::value serialize(const math::transform& t);
	json::value serialize(const math::vec2& v);
	json::value serialize(const math::vec3& v);
	json::value serialize(const math::vec4& v);
	json::value serialize(const ImageAssetPtr& asset);
	json::value serialize(const PrefabAssetPtr& asset);
	json::value serialize(const SceneAssetPtr& asset);
	json::value serialize(const SpriteAnimationAssetPtr& asset);
	json::value serialize(const SpriteAssetPtr& asset);
	json::value serialize(const TextAssetPtr& asset);
	template <typename T>
	json::value serialize(const std::vector<T>& list)
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
	bool deserialize(const json::value& value, IType& type);
	bool deserialize(const json::value& value, uuid& id);
	bool deserialize(const json::value& value, graphics::Color& color);
	bool deserialize(const json::value& value, graphics::TextureCoords& coords);
	bool deserialize(const json::value& value, graphics::TextureRect& rect);
	bool deserialize(const json::value& value, math::transform& t);
	bool deserialize(const json::value& value, math::vec2& v);
	bool deserialize(const json::value& value, math::vec3& v);
	bool deserialize(const json::value& value, math::vec4& v);
	bool deserialize(const json::value& value, ImageAssetPtr& asset);
	bool deserialize(const json::value& value, PrefabAssetPtr& asset);
	bool deserialize(const json::value& value, SceneAssetPtr& asset);
	bool deserialize(const json::value& value, SpriteAnimationAssetPtr& asset);
	bool deserialize(const json::value& value, SpriteAssetPtr& asset);
	bool deserialize(const json::value& value, TextAssetPtr& asset);
};