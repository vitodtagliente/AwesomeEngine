/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>

struct Asset
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

	struct Descriptor
	{
		Descriptor();
		Descriptor(Type type);
		Descriptor(const Descriptor& other);

		Descriptor& operator= (const Descriptor& other);
		bool operator== (const Descriptor& other) const;
		bool operator!= (const Descriptor& other) const; 
		
		inline operator bool() const { return type != Type::None; };

		static Descriptor load(const std::filesystem::path& filename);
		void save(const std::filesystem::path& filename);

		std::filesystem::path getDataPath() const;

		uuid id;
		std::filesystem::path path;
		Type type;
	};

	Asset();
	Asset(const Descriptor& descriptor);
	Asset(const Asset& other) = delete;

	Asset& operator= (const Descriptor& other) = delete;
	bool operator== (const Asset& other) const;
	bool operator!= (const Asset& other) const;

	static bool isAsset(const std::filesystem::path& filename);
	static const std::vector<std::string>& getExtensionsByType(Type type);
	static const std::string& getExtensionByType(Type type);
	static Type getTypeByExtension(const std::string& extension);

	Descriptor descriptor;

	static std::map<Asset::Type, std::vector<std::string>> s_filetypes;
	static constexpr char* const Extension = ".asset";

	REFLECT()
};

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