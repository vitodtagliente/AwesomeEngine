#include "asset_library.h"

#include <fstream>
#include <thread>

#include <awesome/encoding/json.h>

#include "image_asset.h"
#include "prefab_asset.h"
#include "scene_asset.h"
#include "sprite_asset.h"
#include "sprite_animation_asset.h"
#include "text_asset.h"

AssetLibrary::AssetLibrary()
	: m_cache()
	, m_register()
	, m_directory(std::filesystem::current_path().string() + "/../assets")
{

}

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
	static const auto load = [](const std::filesystem::path& filename) -> std::string
	{
		std::ostringstream buf;
		std::ifstream input(filename.c_str());
		buf << input.rdbuf();
		return buf.str();
	};

	if (!std::filesystem::exists(path))
	{
		return nullptr;
	}

	switch (descriptor.type)
	{
	case Asset::Type::Image:
	{
		ImageAssetPtr asset = std::make_shared<ImageAsset>(descriptor);
		std::thread handler([path, asset]()
			{
				asset->data = Image::load(path);
			}
		);
		return handler.detach(), asset;
	}
	case Asset::Type::Prefab:
	{
		PrefabAssetPtr asset = std::make_shared<PrefabAsset>(descriptor);
		std::thread handler([path, asset]()
			{
				asset->data = load(path);
			}
		);
		return handler.detach(), asset;
	}
	case Asset::Type::Scene:
	{
		SceneAssetPtr asset = std::make_shared<SceneAsset>(descriptor);
		std::thread handler([path, asset]() 
			{ 
				asset->data = json::Deserializer::parse(load(path)); 
			}
		);		
		return handler.detach(), asset;
	}
	case Asset::Type::Sprite:
	{
		SpriteAssetPtr asset = std::make_shared<SpriteAsset>(descriptor);
		std::thread handler([path, asset]()
			{
				asset->data = Sprite::load(path);
			}
		);
		return handler.detach(), asset;
	}
	case Asset::Type::SpriteAnimation:
	{
		SpriteAnimationAssetPtr asset = std::make_shared<SpriteAnimationAsset>(descriptor);
		std::thread handler([path, asset]()
			{
				asset->data = SpriteAnimation::load(path);
			}
		);
		return handler.detach(), asset;
	}
	case Asset::Type::Text:
	{
		TextAssetPtr asset = std::make_shared<TextAsset>(descriptor);
		std::thread handler([path, asset]()
			{
				asset->data = load(path);
			}
		);
		return handler.detach(), asset;
	}
	default: return nullptr;
	}
}