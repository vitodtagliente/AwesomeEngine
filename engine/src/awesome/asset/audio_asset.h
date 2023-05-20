/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>

#include "asset.h"
#include "data/audio.h"

#include "audio_asset_generated.h"

template <>
struct ResourceReader<Audio>
{
	using result_type = std::shared_ptr<Audio>;

	template <typename... Args>
	static result_type read(const std::filesystem::path& path, Args&&... args)
	{
		result_type audio = std::make_shared<Audio>();

		const std::string extension = path.extension().string();
		stringToEnum(extension, audio->type);

		return audio;
	};
};

constexpr int AssetType_Audio = 10;

CLASS(Type = Asset)
struct AudioAsset : public Asset
{
	AudioAsset()
		: Asset(AssetType_Audio)
	{}

	AudioAsset(const uuid& _id)
		: Asset(_id, AssetType_Audio)
	{}

	ASSET_GENERATED_BODY(AssetType_Audio, Audio)
	GENERATED_BODY()
};

CLASS(Type = AssetLoader)
struct AudioAssetLoader : public AssetLoader
{
	AudioAssetLoader()
		: AssetLoader()
	{
		extensions = { ".flac", ".mp3", ".wav" };
		type = AssetType_Audio;
	}

	virtual void load(const std::filesystem::path& path) override
	{
		Resource<Audio>::load(path);
	}

	GENERATED_BODY()
};