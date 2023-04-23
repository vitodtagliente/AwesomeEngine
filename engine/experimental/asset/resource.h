/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <thread>

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>

#include "resource_loader.h"

template <typename T, typename L = ResourceLoader<T>>
class Resource
{
public:
	using loader_t = L;
	using resource_t = T;
	using cache_t = std::map<std::filesystem::path, std::weak_ptr<T>>;

	static std::shared_ptr<T> load(const std::filesystem::path& path)
	{
		const auto& it = s_cache.find(path);
		if (it != s_cache.end() && !it->second.expired())
		{
			return it->second.lock();
		}

		std::shared_ptr<T> resource = s_loader(path);
		s_cache.insert(std::make_pair(path, resource));
		return resource;
	}

private:
	static inline loader_t s_loader;
	static inline cache_t s_cache;
};