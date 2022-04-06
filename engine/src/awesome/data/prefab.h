/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

#include <awesome/entity/entity.h>

struct Prefab final
{
	Prefab();
	Prefab(const Entity* const entity);
	Prefab(const Prefab& other);
	~Prefab();

	static Prefab load(const std::filesystem::path& filename);
	void save(const std::filesystem::path& filename);

	Prefab& operator= (const Prefab& other);
	bool operator== (const Prefab& other) const;
	bool operator!= (const Prefab& other) const;

	Entity entity;
};