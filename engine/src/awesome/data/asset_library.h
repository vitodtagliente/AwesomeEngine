/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <chrono>
#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <awesome/core/singleton.h>
#include <awesome/core/uuid.h>

#include "asset.h"

class AssetLibrary : public Singleton<AssetLibrary>
{
public:
	AssetLibrary();
	~AssetLibrary() = default;

	std::shared_ptr<Asset> find(const uuid& id);
	template <typename T>
	std::shared_ptr<T> find(const uuid& id)
	{
		return std::static_pointer_cast<T>(find(id));
	}

	inline const std::filesystem::path& getDirectory() const { return m_directory; }

	void registerDescriptor(const Asset& descriptor);

	std::vector<Asset> list() const;
	std::vector<Asset> list(Asset::Type type) const;


private:

	struct Slot
	{
		Slot(const std::shared_ptr<Asset>& asset)
			: asset(asset)
		{}

		std::shared_ptr<Asset> asset;
	};

	std::shared_ptr<Asset> create(const Asset& asset, const std::filesystem::path& filename);
	bool getRedirector(const uuid& id, std::filesystem::path& filename) const;

	std::map<uuid, Slot> m_cachedAssets;
	std::map<uuid, Asset> m_assetDescriptors;
	std::filesystem::path m_directory;
};