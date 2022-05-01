/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>

REFLECT_ENUM(AssetType,
	None,
	Image,
	Prefab,
	Scene,
	Sprite,
	SpriteAnimation,
	Text
)

struct Asset
{
	typedef AssetType Type;

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
	std::function<void()> onLoad;

	static std::map<Asset::Type, std::vector<std::string>> s_filetypes;
	static constexpr char* const Extension = ".asset";

	REFLECT()
};

typedef std::shared_ptr<Asset> AssetPtr;

template <typename T>
struct AssetTypeInfo final
{
	static Asset::Type get()
	{
		return Asset::Type::None;
	}
};

#define ASSETTYPEINFO(A, T) \
	template <> \
	struct AssetTypeInfo<A> final \
	{ \
		static Asset::Type get() \
		{ \
			return T; \
		}\
	};