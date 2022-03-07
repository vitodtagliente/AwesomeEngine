/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <map>
#include <string>

#include <awesome/core/singleton.h>

#include "asset.h"

class AssetCache
{
public:
	AssetCache() = default;
	~AssetCache() = default;

	// void insert(const Asset& asset);

private:
	std::map<std::string, Asset> m_assets;
};

class AssetLibrary : public Singleton<AssetLibrary>
{
public:


};