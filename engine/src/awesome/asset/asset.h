/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <memory>
#include <thread>
#include <vector>

#include <awesome/asset/asset_library.h>
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

template <int Type, typename T>
struct AssetHandle : public Asset
{
	AssetHandle()
		: Asset(Type)
		, resource(nullptr)
	{

	}

	AssetHandle(const uuid& _id)
		: Asset(Type)
		, resource(nullptr)
	{
		const AssetRecord* const record = AssetLibrary::instance().database.find(_id);
		if (record && type == record->type)
		{
			id = _id;
			path = record->path;
		}
	}

	void load()
	{
		if (id != uuid::Invalid && resource == nullptr && state == State::None)
		{
			state = State::Loading;
			std::thread thread([this]()
				{
					if (path.empty())
					{
						const AssetRecord* const record = AssetLibrary::instance().database.find(id);
						if (record && type == record->type)
						{
							path = record->path;
						}
					}

					if (!path.empty())
					{
						resource = Resource<T>::load(path);
						if (resource != nullptr)
						{
							state = State::Ready;
							if (onLoad) onLoad();
						}
						else
						{
							state = State::Error;
						}
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

	bool save(const std::filesystem::path& _path)
	{
		if (state != State::Ready) return false;

		return ResourcerWriter<T>::write(*resource, _path);
	}

	bool save()
	{
		if (path.string().empty()) return false;

		return save(path);
	}

	virtual void reset() override
	{
		Asset::reset();
		resource = nullptr;
	}

	static AssetHandle get(const AssetRecord& record)
	{
		if (record.type != Type) return {};

		AssetHandle asset(record.id);
		return asset;
	}

	bool ready() const { return state == State::Ready; }

	std::shared_ptr<T> resource;

	static constexpr int Type = Type;
};