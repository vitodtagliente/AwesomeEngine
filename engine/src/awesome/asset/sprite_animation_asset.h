/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/data/type_file.h>

#include "asset.h"
#include "data/sprite_animation.h"

#include "sprite_animation_asset_generated.h"

template <>
struct ResourceReader<SpriteAnimation>
{
	using result_type = std::shared_ptr<SpriteAnimation>;

	template <typename... Args>
	static result_type read(const std::filesystem::path& path, Args&&... args)
	{
		result_type result = std::make_shared<SpriteAnimation>();
		if (TypeFile::load(path, *result))
		{
			return result;
		}
		return nullptr;
	};
};

template <>
struct ResourcerWriter<SpriteAnimation>
{
	static bool write(const SpriteAnimation& data, const std::filesystem::path& path)
	{
		return TypeFile::save(data, path), true;
	}
};

constexpr int AssetType_SpriteAnimation = 5;

CLASS(Type = Asset)
struct SpriteAnimationAsset : public Asset
{
	SpriteAnimationAsset()
		: Asset(AssetType_SpriteAnimation)
	{}

	SpriteAnimationAsset(const uuid& _id)
		: Asset(_id, AssetType_SpriteAnimation)
	{}

	ASSET_GENERATED_BODY(AssetType_SpriteAnimation, SpriteAnimation)
	GENERATED_BODY()
};

CLASS(Type = AssetLoader)
struct SpriteAnimationLoader : public AssetLoader
{
	SpriteAnimationLoader()
		: AssetLoader()
	{
		extensions = { ".spriteanim" };
		type = AssetType_SpriteAnimation;
	}

	virtual void load(const std::filesystem::path& path) override
	{
		Resource<SpriteAnimation>::load(path);
	}

	GENERATED_BODY()
};