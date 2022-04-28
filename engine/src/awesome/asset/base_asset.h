/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <optional>

#include "asset.h"

template <Asset::Type T, typename D>
struct BaseAsset : public Asset
{
public:

	typedef D value_t;

	BaseAsset(const Asset::Descriptor& descriptor)
		: Asset(descriptor)
		, data(std::nullopt)
	{

	}

	BaseAsset(const Asset::Descriptor& descriptor, const std::optional<value_t> data)
		: Asset(descriptor)
		, data(data)
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

	std::optional<value_t> data;
};