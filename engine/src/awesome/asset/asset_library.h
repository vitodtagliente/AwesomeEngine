/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <awesome/core/singleton.h>
#include <awesome/engine/engine_settings.h>

#include "asset.h"
#include "asset_database.h"
#include "asset_handler.h"
#include "asset_type.h"

class AssetLibrary : public Singleton<AssetLibrary>
{
public:
	friend struct Asset;

	AssetLibrary() = default;
	~AssetLibrary() = default;

	inline const std::filesystem::path& path() const { return m_path; }

	void init(EngineMode mode, const std::filesystem::path& path);

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

	inline const std::vector<AssetHandler>& handlers() const { return m_handlers; }

	const AssetHandler* const findHandler(const std::filesystem::path& path) const;
	std::shared_ptr<Asset> create(const AssetHandler& handler, const AssetRecord& record);

	std::map<uuid, Slot> m_cache;
	std::vector<AssetHandler> m_handlers;
	std::filesystem::path m_path;
};