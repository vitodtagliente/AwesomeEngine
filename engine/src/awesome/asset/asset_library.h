/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <awesome/core/singleton.h>

#include "asset.h"
#include "asset_database.h"
#include "asset_type.h"

struct AssetHandler
{
	std::function<AssetPtr()> create;
	std::vector<std::string> extensions;
	std::string name;
	int type{ AssetType_Invalid };
};

class AssetLibrary : public Singleton<AssetLibrary>
{
public:
	AssetLibrary() = default;
	~AssetLibrary() = default;

	inline const std::vector<AssetHandler>& handlers() const { return m_handlers; }
	inline const std::filesystem::path& path() const { return m_path; }

	void add(const AssetHandler& handler);
	void init(const std::filesystem::path& path);

	AssetPtr find(const uuid& id);
	template <typename T>
	std::shared_ptr<T> find(const uuid& id)
	{
		return std::static_pointer_cast<T>(find(id));
	}

	void release(const AssetPtr& asset);
	void release(const uuid& id);

	AssetDatabase database;

private:
	struct Slot
	{
		Slot(const std::weak_ptr<Asset>& asset)
			: asset(asset)
		{}

		inline bool expired() const { return asset.expired(); }

		std::weak_ptr<Asset> asset;
	};

	const AssetHandler* const findHandler(const std::filesystem::path& path) const;
	std::shared_ptr<Asset> create(const AssetHandler& handler, const AssetRecord& record);

	std::map<uuid, Slot> m_cache;
	std::vector<AssetHandler> m_handlers;
	std::filesystem::path m_path;
};