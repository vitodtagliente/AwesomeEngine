/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>
#include <vector>

#include <awesome/core/singleton.h>

#include "asset_database.h"

class AssetLibrary : public Singleton<AssetLibrary>
{
public:
	friend struct Asset;

	AssetLibrary() = default;
	~AssetLibrary() = default;

	inline const std::vector<std::unique_ptr<AssetLoader>>& loaders() const { return m_loaders; }
	inline const std::filesystem::path& path() const { return m_path; }

	void init(const std::filesystem::path& path);

	AssetDatabase database;

private:
	std::vector<std::unique_ptr<AssetLoader>> m_loaders;
	std::filesystem::path m_path;
};