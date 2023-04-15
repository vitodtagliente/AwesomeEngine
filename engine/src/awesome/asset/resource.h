/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <thread>

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

template <typename T, typename L = ResourceLoader<T>>
class FAsset
{
public:
	enum class State
	{
		None,
		Error,
		Loading,
		Ready
	};

	void preload() { resource(); }

	const uuid& id() const { return m_id; }
	FAsset& operator= (const uuid& id)
	{
		if (m_id != id)
		{
			m_id = id;
			m_resource = nullptr;
			m_state = State::None;
		}
		return *this;
	}

	const std::shared_ptr<T>& resource() const
	{
		if (m_id != uuid::Invalid && m_resource == nullptr && m_state == State::None)
		{
			m_state = State::Loading;
			std::thread thread([this]()
				{
					m_resource = Resource<T, L>::load("");
					if (m_resource != nullptr)
					{
						m_state = State::Ready;
					}
					else
					{
						m_state = State::Error;
					}
				}
			);
			thread.detach();
		}
		return m_resource;
	}

	State state() const { return m_state; }

	operator bool() const
	{
		return m_id != uuid::Invalid;
	}

	void reset()
	{
		m_id = uuid::Invalid;
		m_resource = nullptr;
		m_state = State::None;
	}

private:
	uuid m_id;
	mutable std::shared_ptr<T> m_resource;
	State m_state{ State::None };
};