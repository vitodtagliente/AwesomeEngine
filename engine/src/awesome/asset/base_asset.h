/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "asset.h"

template <Asset::Type T, typename D>
struct BaseAsset : public Asset
{
public:
	typedef D data_t;

	BaseAsset(const Asset::Descriptor& descriptor)
		: Asset(descriptor)
		, data()
	{

	}

	BaseAsset(const BaseAsset& other) = delete;

	BaseAsset& operator= (const BaseAsset& other) = delete;

	bool operator== (const BaseAsset& other) const
	{
		return descriptor.id == other.descriptor.id;
	}

	bool operator!= (const BaseAsset& other) const
	{
		return descriptor.id != other.descriptor.id;
	}

	data_t data;
};