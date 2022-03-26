/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>

#include <awesome/core/reflection.h>
#include <awesome/core/serialization.h>
#include <awesome/core/uuid.h>

#include "image.h"

struct Asset : public ISerializable
{
	enum class Type : int
	{
		None,
		Image,
		Prefab,
		Text
	};

	Asset();
	Asset(Type type);
	Asset(Type type, const uuid& id);
	Asset(const Asset& asset);

	Asset& operator= (const Asset& other);
	bool operator== (const Asset& other) const;
	bool operator!= (const Asset& other) const;
	inline operator bool() const { return type != Type::None; };

	// serialization
	virtual json::value serialize() const override;
	virtual void deserialize(const json::value& value) override;

	static Asset load(const std::string& filename);
	static bool isAsset(const std::string& filename);
	static bool isAsset(const std::filesystem::path& filename);
	static constexpr char* const Extension = ".asset";

	uuid id;
	Type type;
	std::string filename;

	REFLECT()
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

	BaseAsset(const D& data, const Asset& descriptor)
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

typedef BaseAsset<Asset::Type::Image, Image> ImageAsset;
typedef BaseAsset<Asset::Type::Text, std::string> TextAsset;