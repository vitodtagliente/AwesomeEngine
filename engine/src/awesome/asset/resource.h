/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <thread>

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>

template <typename T>
struct ResourceReader
{
	using result_type = std::shared_ptr<T>;

	template <typename... Args>
	static result_type read(const std::filesystem::path&, Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	};
};

template <typename T>
struct ResourcerWriter
{
	static bool write(const T&, const std::filesystem::path&)
	{
		return false;
	}
};

template <typename T>
class Resource
{
public:
	using resource_t = T;
	using cache_t = std::map<std::filesystem::path, std::weak_ptr<T>>;

	static std::shared_ptr<T> load(const std::filesystem::path& path)
	{
		const auto& it = s_cache.find(path);
		if (it != s_cache.end() && !it->second.expired())
		{
			return it->second.lock();
		}

		std::shared_ptr<T> resource = ResourceReader<T>::read(path);
		s_cache.insert(std::make_pair(path, resource));
		return resource;
	}

private:
	static inline cache_t s_cache;
};