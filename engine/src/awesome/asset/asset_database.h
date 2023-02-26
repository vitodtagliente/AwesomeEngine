/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>

struct AssetRecord
{
	uuid id;
	std::filesystem::path path;
	int type;

	void save(const std::filesystem::path& path);
};

struct AssetDatabase
{
	bool erase(const uuid& id);
	bool exists(const uuid& id) const;
	bool exists(const std::filesystem::path& path) const;
	const AssetRecord* const find(const uuid& id) const;
	const AssetRecord* const find(const std::filesystem::path& path) const;
	bool insert(const AssetRecord& record);

	void save() const;
	bool load(const std::filesystem::path& path);

	std::filesystem::path path;
	std::vector<AssetRecord> records;

	static constexpr char* const Filename = "assets.json";
};