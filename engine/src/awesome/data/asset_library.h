/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <chrono>
#include <map>
#include <memory>
#include <string>

#include <awesome/core/singleton.h>
#include <awesome/core/uuid.h>

#include "asset.h"

class AssetCache
{
public:
	AssetCache();
	~AssetCache() = default;

	void insert(const std::shared_ptr<Asset>& asset);
	std::shared_ptr<Asset> find(const uuid& id) const;
	void update();

private:

	struct Slot
	{
		Slot(const std::shared_ptr<Asset>& asset)
			: asset(asset)
		{}

		std::shared_ptr<Asset> asset;
	};

	std::map<uuid, Slot> m_assets;
};

class AssetLibrary : public Singleton<AssetLibrary>
{
public:
	AssetLibrary();
	~AssetLibrary() = default;

	std::shared_ptr<Asset> find(Asset::Type type, const uuid& id);
	std::shared_ptr<Asset> find(Asset::Type type, const std::string& filename);

	std::map<uuid, std::string> redirectors;

private:
	AssetCache& getCache(Asset::Type type);
	std::shared_ptr<Asset> create(Asset::Type type, const std::string& filename);
	bool getRedirector(const uuid& id, std::string& filename) const;
	bool getRedirector(const std::string& filename, uuid& id) const;

	std::map<Asset::Type, AssetCache> m_caches;
};