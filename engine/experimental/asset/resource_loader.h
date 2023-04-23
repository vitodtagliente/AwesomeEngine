/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>

template <typename T>
struct ResourceLoader
{
	using result_type = std::shared_ptr<T>;

	template <typename... Args>
	result_type operator()(const std::filesystem::path&, Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	};
};