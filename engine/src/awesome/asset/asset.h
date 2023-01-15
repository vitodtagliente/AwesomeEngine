/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <memory>

#include <awesome/core/uuid.h>

#include "asset_generated.h"

CLASS()
struct Asset : public Type
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

	virtual bool load(const std::filesystem::path&) { return false; }
	virtual bool save(const std::filesystem::path&) const { return false; }

	PROPERTY() uuid id;
	std::function<void()> onLoad;
	std::filesystem::path path;
	State state{ State::None };

	static constexpr char* const Extension = ".asset";

	GENERATED_BODY()
};

typedef std::shared_ptr<Asset> AssetPtr;