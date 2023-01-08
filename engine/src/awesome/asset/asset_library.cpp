#include "asset_library.h"

#include <thread>

#include <awesome/core/serialization.h>
#include <awesome/data/json_file.h>
#include <awesome/data/text_file.h>

#include "custom_asset.h"
#include "image_asset.h"
#include "prefab_asset.h"
#include "scene_asset.h"
#include "sprite_animation_asset.h"
#include "text_asset.h"
#include "tileset_asset.h"

void AssetLibrary::unload(const uuid& id)
{
	m_cache.erase(id);
}

void AssetLibrary::insert(const Asset::Descriptor& descriptor)
{
	m_register[descriptor.id] = descriptor;
}

void AssetLibrary::remove(const uuid& id)
{
	m_register.erase(id);
}

std::vector<Asset::Descriptor> AssetLibrary::list() const
{
	std::vector<Asset::Descriptor> result;
	for (const auto& pair : m_register)
	{
		result.push_back(pair.second);
	}
	return result;
}

std::vector<Asset::Descriptor> AssetLibrary::list(const Asset::Type type) const
{
	std::vector<Asset::Descriptor> result;
	for (const auto& pair : m_register)
	{
		if (pair.second.type == type)
		{
			result.push_back(pair.second);
		}
	}
	return result;
}

std::shared_ptr<Asset> AssetLibrary::find(const uuid& id)
{
	const auto& cacheIt = m_cache.find(id);
	if (cacheIt != m_cache.end() && !cacheIt->second.isExpired())
	{
		return cacheIt->second.asset.lock();
	}

	const auto& registerIt = m_register.find(id);
	if (registerIt == m_register.end())
	{
		return nullptr;
	}

	Asset::Descriptor& descriptor = registerIt->second;
	std::shared_ptr<Asset> asset = create(descriptor, descriptor.getDataPath());
	m_cache.insert(std::make_pair(descriptor.id, Slot(asset)));
	return asset;
}

std::shared_ptr<Asset> AssetLibrary::create(const Asset::Descriptor& descriptor, const std::filesystem::path& path)
{
	if (!std::filesystem::exists(path))
	{
		return nullptr;
	}

	switch (descriptor.type)
	{
	case Asset::Type::Custom:
	{
		CustomAssetPtr asset = std::make_shared<CustomAsset>(descriptor);
		asset->state = Asset::State::Loading;
		std::thread handler(
			[path, asset]() -> void
			{
				JsonFile::load(path, asset->data.value());
				asset->state = Asset::State::Ready;
				if (asset->onLoad) asset->onLoad();
			}
		);
		return handler.detach(), asset;
	}
	case Asset::Type::Image:
	{
		ImageAssetPtr asset = std::make_shared<ImageAsset>(descriptor);
		asset->state = Asset::State::Loading;
		std::thread handler([path, asset]()
			{
				asset->data = Image::load(path);
				asset->state = Asset::State::Ready;
				if (asset->onLoad) asset->onLoad();
			}
		);
		return handler.detach(), asset;
	}
	case Asset::Type::Prefab:
	{
		PrefabAssetPtr asset = std::make_shared<PrefabAsset>(descriptor);
		asset->state = Asset::State::Loading;
		std::thread handler([path, asset]()
			{
				asset->data = json::value();
				JsonFile::load(path, asset->data.value());
				asset->state = Asset::State::Ready;
				if (asset->onLoad) asset->onLoad();
			}
		);
		return handler.detach(), asset;
	}
	case Asset::Type::Scene:
	{
		SceneAssetPtr asset = std::make_shared<SceneAsset>(descriptor);
		asset->state = Asset::State::Loading;
		std::thread handler([path, asset]()
			{
				asset->data = json::value();
				JsonFile::load(path, asset->data.value());
				asset->state = Asset::State::Ready;
				if (asset->onLoad) asset->onLoad();
			}
		);		
		return handler.detach(), asset;
	}
	case Asset::Type::SpriteAnimation:
	{
		SpriteAnimationAssetPtr asset = std::make_shared<SpriteAnimationAsset>(descriptor);
		asset->state = Asset::State::Loading;
		asset->data = SpriteAnimationData();
		std::thread handler(
			[path, asset]() -> void
			{
				json::value data;
				JsonFile::load(path, data);
				Deserializer::deserialize(data, asset->data.value());
				asset->state = Asset::State::Ready;
				if (asset->onLoad) asset->onLoad();
			}
		);
		return handler.detach(), asset;
	}
	case Asset::Type::Text:
	{
		TextAssetPtr asset = std::make_shared<TextAsset>(descriptor);
		asset->state = Asset::State::Loading;
		std::thread handler([path, asset]()
			{
				asset->data = "";
				TextFile::load(path, asset->data.value());
				asset->state = Asset::State::Ready;
				if (asset->onLoad) asset->onLoad();
			}
		);
		return handler.detach(), asset;
	}
	case Asset::Type::Tileset:
	{
		TilesetAssetPtr asset = std::make_shared<TilesetAsset>(descriptor);
		asset->state = Asset::State::Loading;
		asset->data = Tileset();
		std::thread handler(
			[path, asset]() -> void
			{
				JsonFile::load(path, asset->data.value());
				asset->state = Asset::State::Ready;
				if (asset->onLoad) asset->onLoad();
			}
		);
		return handler.detach(), asset;
	}
	default: return nullptr;
	}
}