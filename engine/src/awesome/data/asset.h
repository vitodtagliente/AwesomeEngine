/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/serialization.h>
#include <awesome/core/uuid.h>

#include "image.h"

struct Asset : public ISerializable
{
	enum class Type : int
	{
		None,
		Image,
		Prefab
	};

	Asset()
		: id()
		, type(Type::None)
	{

	}

	Asset(const Type type)
		: id()
		, type(type)
	{

	}

	Asset(const Type type, const uuid& id)
		: id(id)
		, type(type)
	{

	}

	Asset(const Asset& asset)
		: id(asset.id)
		, type(asset.type)
	{

	}

	Asset& operator= (const Asset& other)
	{
		id = other.id;
		type = other.type;
		return *this;
	}

	bool operator== (const Asset& other) const
	{
		return id == other.id && type == other.type;
	}

	bool operator!= (const Asset& other) const
	{
		return id != other.id || type != other.type;
	}

	virtual json::value serialize() const override
	{
		return json::object({
			{"id", ::serialize(id)},
			{"type", static_cast<int>(type)}
			});
	}

	uuid id;
	Type type;
};

template <Asset::Type T, typename D>
struct BaseAsset : public Asset
{
public:

	BaseAsset()
		: Asset(T)
		, data()
	{

	}

	BaseAsset(const D& data)
		: Asset(T)
		, data(data)
	{

	}

	BaseAsset(const D& data, const uuid& id)
		: Asset(T, id)
		, data(data)
	{

	}

	BaseAsset(const BaseAsset& asset)
		: Asset(asset)
		, data(asset.data)
	{

	}

	BaseAsset& operator= (const BaseAsset& other)
	{
		id = other.id;
		type = other.type;
		data = other.data;
		return *this;
	}

	bool operator== (const BaseAsset& other) const
	{
		return id == other.id && type == other.type && data == other.data;
	}

	bool operator!= (const BaseAsset& other) const
	{
		return id != other.id || type != other.type || data != other.data;
	}

	D data;
};

typedef BaseAsset<Asset::Type::Image, Image> ImageAsset;