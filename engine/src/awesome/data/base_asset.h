/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <optional>

#include "asset.h"

template <Asset::Type T, typename D>
struct BaseAsset : public Asset
{
public:

	BaseAsset(const Asset::Descriptor& descriptor, const std::optional<D> data)
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

	std::optional<D> data;
};