/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <chrono>
#include <map>
#include <memory>
#include <string>

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

	inline const std::string& getDirectory() const { return m_directory; }

	std::map<uuid, std::string> redirectors;

private:

	struct Slot
	{
		Slot(const std::shared_ptr<Asset>& asset)
			: asset(asset)
		{}

		std::shared_ptr<Asset> asset;
	};

	std::shared_ptr<Asset> create(const Asset& asset, const std::string& filename);
	bool getRedirector(const uuid& id, std::string& filename) const;

	std::map<uuid, Slot> m_assets;
	std::string m_directory;
};