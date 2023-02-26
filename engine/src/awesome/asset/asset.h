/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <memory>

#include <awesome/core/uuid.h>

#include "asset_type.h"

struct Asset
{
	enum class State
	{
		None,
		Error,
		Loading,
		Ready
	};

	Asset() = default;
	virtual ~Asset() = default;
	Asset(const Asset& other) = delete;

	Asset& operator= (const Asset& other) = delete;
	bool operator== (const Asset& other) const;
	bool operator!= (const Asset& other) const;

	virtual bool load(const std::filesystem::path&) = 0;
	virtual bool save(const std::filesystem::path&) const = 0;
	
	uuid id;
	std::filesystem::path path;
	State state{ State::None };
	int type{ AssetType_Invalid };

	// events
	std::function<void()> onLoad;

	static std::shared_ptr<Asset> create(int type);
	bool static isSupported(const std::filesystem::path& path);
	bool static isSupported(const std::filesystem::path& path, int& type);

	static constexpr char* const Extension = ".asset";
};

typedef std::shared_ptr<Asset> AssetPtr;