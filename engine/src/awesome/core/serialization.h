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

template <typename T>
json::value serialize(const T& data)
{
	const IType* const type = dynamic_cast<const IType* const>(&data);
	if (type != nullptr)
	{
		return serialize(*type);
	}
	return json::value();
}

template <typename T>
bool deserialize(const json::value& value, T& data) 
{
	IType* const type = dynamic_cast<IType* const>(&data);
	if (type != nullptr)
	{
		return deserialize(value, *type);
	}
	return false; 
}

template <> json::value serialize(const IType& type);
template <> json::value serialize(const bool& primitive);
template <> json::value serialize(const int& primitive);
template <> json::value serialize(const float& primitive);
template <> json::value serialize(const double& primitive);
template <> json::value serialize(const char& primitive);
template <> json::value serialize(const uuid& id);
template <> json::value serialize(const graphics::Color& color);
template <> json::value serialize(const graphics::TextureCoords& coords);
template <> json::value serialize(const graphics::TextureRect& rect);
template <> json::value serialize(const math::transform& t);
template <> json::value serialize(const math::vec2& v);
template <> json::value serialize(const math::vec3& v);
template <> json::value serialize(const math::vec4& v);
template <> json::value serialize(const ImageAssetPtr& asset);
template <> json::value serialize(const PrefabAssetPtr& asset);
template <> json::value serialize(const SceneAssetPtr& asset);
template <> json::value serialize(const SpriteAnimationAssetPtr& asset);
template <> json::value serialize(const SpriteAssetPtr& asset);
template <> json::value serialize(const TextAssetPtr& asset);

template <typename T>
json::value serialize(const std::vector<T>& list)
{
	json::value data = json::array();
	for (const auto& element : list)
	{
		data.push_back(::serialize(element));
	}
	return data;
}

template <> bool deserialize(const json::value& value, IType& type);
template <> bool deserialize(const json::value& value, uuid& id);
template <> bool deserialize(const json::value& value, graphics::Color& color);
template <> bool deserialize(const json::value& value, graphics::TextureCoords& coords);
template <> bool deserialize(const json::value& value, graphics::TextureRect& rect);
template <> bool deserialize(const json::value& value, math::transform& t);
template <> bool deserialize(const json::value& value, math::vec2& v);
template <> bool deserialize(const json::value& value, math::vec3& v);
template <> bool deserialize(const json::value& value, math::vec4& v);
template <> bool deserialize(const json::value& value, ImageAssetPtr& asset);
template <> bool deserialize(const json::value& value, PrefabAssetPtr& asset);
template <> bool deserialize(const json::value& value, SceneAssetPtr& asset);
template <> bool deserialize(const json::value& value, SpriteAnimationAssetPtr& asset);
template <> bool deserialize(const json::value& value, SpriteAssetPtr& asset);
template <> bool deserialize(const json::value& value, TextAssetPtr& asset);