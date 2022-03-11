/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/uuid.h>

#include "image.h"

class Asset
{
public:
	enum class Type
	{
		Image,
		Prefab
	};

	Asset(const Type type)
		: m_id()
		, m_type(type)
	{

	}

	inline const uuid& getId() const { return m_id; }
	inline Type getType() const { return m_type; }

private:
	uuid m_id;
	Type m_type;
};

template <Asset::Type T, typename D>
class BaseAsset : public Asset
{
public:
	BaseAsset(const D& data)
		: Asset(T)
		, data(data)
	{

	}

	D data;
};

typedef BaseAsset<Asset::Type::Image, Image> ImageAsset;