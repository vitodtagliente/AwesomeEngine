/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/uuid.h>

#include "image.h"

class Asset
{
public:
	friend class AssetLibrary;

	enum class Type
	{
		Image,
		Prefab
	};

	inline const uuid& getId() const { return m_id; }
	inline Type getType() const { return m_type; }

protected:
	Asset(const Type type)
		: m_id()
		, m_type(type)
	{

	}

private:
	uuid m_id;
	Type m_type;
};

template <Asset::Type T, typename D>
class BaseAsset : public Asset
{
public:
	D data;

private:
	BaseAsset(const D& data)
		: Asset(T)
		, m_data(data)
	{

	}
};

typedef BaseAsset<Asset::Type::Image, Image> ImageAsset;