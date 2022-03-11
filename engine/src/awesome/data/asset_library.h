/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>

#include <awesome/core/singleton.h>
#include <awesome/core/uuid.h>

#include "asset.h"

class AssetCache
{
public:
	AssetCache();
	~AssetCache() = default;

	void insert(Asset* const asset);
	Asset* const find(const uuid& id) const;
	void free(const uuid& id);

private:

	struct Slot
	{
		Slot(Asset* const asset)
			: asset(asset)
		{}

		Asset* const asset;
	};

	std::map<uuid, Slot> m_assets;
};

class AssetLibrary : public Singleton<AssetLibrary>
{
public:
	AssetLibrary();
	~AssetLibrary() = default;

	Asset* const find(Asset::Type type, const uuid& id);
	Asset* const find(Asset::Type type, const std::string& filename);

	std::map<uuid, std::string> redirectors;

private:
	AssetCache& getCache(Asset::Type type);
	Asset* const create(Asset::Type type, const std::string& filename);
	bool getRedirector(const uuid& id, std::string& filename) const;
	bool getRedirector(const std::string& filename, uuid& id) const;

	std::map<Asset::Type, AssetCache> m_caches;
};