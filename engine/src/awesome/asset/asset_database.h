/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>

#include "asset_database_generated.h"

CLASS()
struct AssetRecord : public IType
{
	PROPERTY() uuid id { uuid::Invalid };
	std::filesystem::path path;
	PROPERTY() int type{ 0 };

	void save(const std::filesystem::path& path);

	AssetRecord& operator= (const AssetRecord& other);
	bool operator== (const AssetRecord& other) const;
	bool operator!= (const AssetRecord& other) const;

	GENERATED_BODY()
};

CLASS()
struct AssetDatabase : public IType
{
	bool erase(const uuid& id);
	bool exists(const uuid& id) const;
	bool exists(const std::filesystem::path& path) const;
	const AssetRecord* const find(const uuid& id) const;
	const AssetRecord* const find(const std::filesystem::path& path) const;
	bool insert(const AssetRecord& record);

	void save() const;
	bool load(const std::filesystem::path& path);

	PROPERTY() std::filesystem::path path;
	PROPERTY() std::vector<AssetRecord> records;

	static constexpr char* const Filename = "assets.json";

	GENERATED_BODY()
};