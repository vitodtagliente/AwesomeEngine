/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <memory>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>

#include "asset_database.h"
#include "resource.h"

#include "asset_generated.h"

CLASS()
struct Asset : public IType
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

	Asset(const uuid& _id, const int _type)
		: id(_id)
		, path()
		, state(State::None)
		, type(_type)
	{

	}

	Asset& operator= (const Asset& other);
	Asset& operator= (const AssetRecord& other);
	bool operator== (const Asset& other) const;
	bool operator!= (const Asset& other) const;

	operator bool() const
	{
		return id != uuid::Invalid;
	}

	bool ready() const
	{
		return state == State::Ready;
	}

	static const AssetRecord* const find(const uuid& id);

	static const std::vector<std::string>& extensions(int type);
	static bool isSupported(const std::filesystem::path& path);
	static bool isSupported(const std::filesystem::path& path, int& type);

	PROPERTY() uuid id;
	std::filesystem::path path;
	State state{ State::None };
	PROPERTY() int type{ AssetType_Invalid };

	static constexpr char* const Extension = ".asset";

	GENERATED_BODY()
};

#define ASSET_GENERATED_BODY(AssetType, T) \
	virtual void type_initialize() override \
	{ \
		load(); \
	} \
	\
	void load(const std::function<void()>& callback = {}) \
	{ \
		if (id != uuid::Invalid && resource == nullptr && state == State::None) \
		{ \
			state = State::Loading; \
			if (path.empty()) \
			{ \
				const AssetRecord* const record = Asset::find(id); \
				if (record && type == record->type) \
				{ \
					path = record->path; \
				} \
			} \
			\
			if (!path.empty()) \
			{ \
				resource = Resource<T>::load(path); \
				if (resource != nullptr) \
				{ \
					state = State::Ready; \
					if (callback) callback(); \
				} \
				else \
				{ \
					state = State::Error; \
				} \
			} \
			else \
			{ \
				state = State::Error; \
			} \
		} \
	} \
	\
	bool save(const std::filesystem::path& _path) \
	{ \
		if (state != State::Ready) return false; \
		\
		return ResourcerWriter<T>::write(*resource, _path); \
	} \
	\
	bool save() \
	{ \
		if (path.string().empty()) return false; \
		\
		return save(path); \
	} \
	\
	std::shared_ptr<T> resource; \
	\
	static constexpr int Type = AssetType;