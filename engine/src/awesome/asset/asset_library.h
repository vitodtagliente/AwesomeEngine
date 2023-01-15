/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <awesome/core/singleton.h>

#include "asset.h"
#include "common_asset_identifier.h"

#include "asset_library_generated.h"

CLASS()
struct AssetRecord : public Type
{
	PROPERTY() uuid id;
	PROPERTY() std::filesystem::path path;
	PROPERTY() std::string type;

	GENERATED_BODY()
};

CLASS()
struct AssetDatabase : public Type
{
	bool erase(const uuid& id);
	bool exists(const uuid& id) const;
	bool exists(const std::filesystem::path& path) const;
	AssetRecord* const find(const uuid& id) const;
	AssetRecord* const find(const std::filesystem::path& path) const;
	bool insert(const std::filesystem::path& path, const std::string& type);

	bool dirty{ false };
	PROPERTY() std::vector<std::unique_ptr<AssetRecord>> records;

	static constexpr char* const Filename = "assets.json";

	GENERATED_BODY()
};

class AssetLibrary : public Singleton<AssetLibrary>
{
public:
	AssetLibrary() = default;
	~AssetLibrary() = default;

	void init(const std::filesystem::path path);
	void flush();

	inline const std::filesystem::path& getDirectory() const { return m_directory; }

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

		inline bool isExpired() const { return asset.expired(); }

		std::weak_ptr<Asset> asset;
	};

	std::shared_ptr<Asset> create(const std::filesystem::path& path);

	std::map<uuid, Slot> m_cache;
	std::filesystem::path m_directory;
};