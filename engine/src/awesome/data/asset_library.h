/// Copyright (c) Vito Domenico Tagliente
#pragma once

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

	AssetPtr find(const uuid& id);
	template <typename T>
	std::shared_ptr<T> find(const uuid& id)
	{
		return std::static_pointer_cast<T>(find(id));
	}

	void unload(const uuid& id);

	inline const std::filesystem::path& getDirectory() const { return m_directory; }

	void insert(const AssetDescriptor& descriptor);
	void remove(const uuid& id);

	std::vector<AssetDescriptor> list() const;
	std::vector<AssetDescriptor> list(Asset::Type type) const;


private:

	struct Slot
	{
		Slot(const std::weak_ptr<Asset>& asset)
			: asset(asset)
		{}

		inline bool isExpired() const { return asset.expired(); }

		std::weak_ptr<Asset> asset;
	};

	std::shared_ptr<Asset> create(const AssetDescriptor& descriptor, const std::filesystem::path& filename);
	bool getRedirector(const uuid& id, std::filesystem::path& filename) const;

	std::map<uuid, Slot> m_cache;
	std::map<uuid, AssetDescriptor> m_register;
	std::filesystem::path m_directory;
};