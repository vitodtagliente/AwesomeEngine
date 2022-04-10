/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

struct Scene final
{
	Scene();
	Scene(const Scene& other);
	~Scene();

	static Scene load(const std::filesystem::path& filename);
	void save(const std::filesystem::path& filename);

	Scene& operator= (const Scene& other);
	bool operator== (const Scene& other) const;
	bool operator!= (const Scene& other) const;
};