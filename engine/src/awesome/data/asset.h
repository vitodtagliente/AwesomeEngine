/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>
#include <set>
#include <string>

#include <awesome/core/reflection.h>
#include <awesome/core/serialization.h>
#include <awesome/core/uuid.h>

struct Asset : public ISerializable
{
	enum class Type : int
	{
		None,
		Image,
		Prefab,
		Sprite,
		SpriteAnimation,
		Text,
		Scene
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

	static Asset load(const std::filesystem::path& filename);
	static bool isAsset(const std::filesystem::path& filename);
	static constexpr char* const Extension = ".asset";

	static const std::set<std::string>& getExtensions(Type type);
	static Type getTypeByExtension(const std::string& extension);

	uuid id;
	Type type;
	std::filesystem::path filename;

	static std::map<Asset::Type, std::set<std::string>> s_filetypes;

	REFLECT()
};

typedef Asset AssetDescriptor;
typedef std::shared_ptr<Asset> AssetPtr;

template <typename T>
struct AssetType final
{
	static Asset::Type get()
	{
		return Asset::Type::None;
	}
};

#define ASSETTYPE(A, T) \
	template <> \
	struct AssetType<A> final \
	{ \
		static Asset::Type get() \
		{ \
			return T; \
		}\
	};