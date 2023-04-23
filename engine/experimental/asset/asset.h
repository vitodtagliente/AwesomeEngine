/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <memory>
#include <vector>

#include <awesome/core/uuid.h>

#include "resource.h"

constexpr int AssetType_Invalid = 0;

struct Asset
{
	enum class State
	{
		None,
		Error,
		Loading,
		Ready
	};

	Asset()
		: id(uuid::Invalid)
		, path()
		, state(State::None)
		, type(AssetType_Invalid)
	{

	}

	Asset(const int _type)
		: id(uuid::Invalid)
		, path()
		, state(State::None)
		, type(_type)
	{

	}

	Asset& operator= (const uuid& _id)
	{
		if (id != _id)
		{
			reset();
			id = _id;
		}
		return *this;
	}

	bool operator== (const Asset& other) const;
	bool operator!= (const Asset& other) const;

	operator bool() const
	{
		return id != uuid::Invalid;
	}

	virtual void reset()
	{
		id = uuid::Invalid;
		state = State::None;
	}

	std::function<void()> onLoad;

	static const std::vector<std::string>& extensions(int type);
	static bool isSupported(const std::filesystem::path& path);
	static bool isSupported(const std::filesystem::path& path, int& type);

	static constexpr char* const Extension = ".asset";

	uuid id;
	std::filesystem::path path;
	State state{ State::None };
	int type{ AssetType_Invalid };
};

template <int Type, typename T, typename L = ResourceLoader<T>>
struct AssetHandle : public Asset
{
	AssetHandle()
		: Asset(Type)
		, resource(nullptr)
	{

	}

	void load()
	{
		if (id != uuid::Invalid && resource == nullptr && state == State::None)
		{
			state = State::Loading;
			std::thread thread([this]()
				{
					resource = Resource<T, L>::load("");
					if (resource != nullptr)
					{
						state = State::Ready;
					}
					else
					{
						state = State::Error;
					}
				}
			);
			thread.detach();
		}
	}

	virtual void reset() override
	{
		Asset::reset();
		resource = nullptr;
	}
	
	std::shared_ptr<T> resource;
};