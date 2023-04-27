/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

#include <awesome/core/singleton.h>
#include <awesome/engine/engine_settings.h>

#include "asset_database.h"

class AssetLibrary : public Singleton<AssetLibrary>
{
public:
	friend struct Asset;

	AssetLibrary() = default;
	~AssetLibrary() = default;

	inline const std::filesystem::path& path() const { return m_path; }

	void init(EngineMode mode, const std::filesystem::path& path);

	AssetDatabase database;

private:
	std::filesystem::path m_path;
};