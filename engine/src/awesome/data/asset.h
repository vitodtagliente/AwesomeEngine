/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/uuid.h>

#include "image.h"

struct Asset
{
	enum class Type
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

	BaseAsset(const uuid& id, const D& data)
		: Asset(T, id)
		, data(data)
	{

	}
	D data;
};

typedef BaseAsset<Asset::Type::Image, Image> ImageAsset;