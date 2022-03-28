/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset.h"

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

	BaseAsset(const D& data, const AssetDescriptor& descriptor)
		: Asset(descriptor)
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
		filename = other.filename;
		return *this;
	}

	bool operator== (const BaseAsset& other) const
	{
		return id == other.id;
	}

	bool operator!= (const BaseAsset& other) const
	{
		return id != other.id;
	}

	D data;
};