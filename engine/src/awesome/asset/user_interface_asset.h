/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/data/type_file.h>

#include "asset.h"
#include "data/user_interface.h"

#include "user_interface_asset_generated.h"

template <>
struct ResourceReader<UserInterface>
{
	using result_type = std::shared_ptr<UserInterface>;

	template <typename... Args>
	static result_type read(const std::filesystem::path& path, Args&&... args)
	{
		result_type result = std::make_shared<UserInterface>();
		if (TypeFile::load(path, *result))
		{
			return result;
		}
		return nullptr;
	};
};

template <>
struct ResourcerWriter<UserInterface>
{
	static bool write(const UserInterface& data, const std::filesystem::path& path)
	{
		return TypeFile::save(data, path), true;
	}
};

constexpr int AssetType_UserInterface = 7;

CLASS(Type = Asset)
struct UserInterfaceAsset : public Asset
{
	UserInterfaceAsset()
		: Asset(AssetType_UserInterface)
	{}

	UserInterfaceAsset(const uuid& _id)
		: Asset(_id, AssetType_UserInterface)
	{}

	ASSET_GENERATED_BODY(AssetType_UserInterface, UserInterface)
	GENERATED_BODY()
};

CLASS(Type = AssetLoader)
struct UserInterfaceAssetLoader : public AssetLoader
{
	UserInterfaceAssetLoader()
		: AssetLoader()
	{
		extensions = { ".ui" };
		type = AssetType_UserInterface;
	}

	virtual void load(const std::filesystem::path& path) override
	{
		Resource<UserInterface>::load(path);
	}

	GENERATED_BODY()
};