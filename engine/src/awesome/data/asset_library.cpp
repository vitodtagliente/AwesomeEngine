#include "asset_library.h"

#include <fstream>

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

void AssetLibrary::remove(const uuid& id)
{
	m_cache.erase(id);
}

void AssetLibrary::insert(const AssetDescriptor& descriptor)
{
	m_register.insert(std::make_pair(descriptor.id, descriptor));
}

std::vector<Asset> AssetLibrary::list() const
{
	std::vector<Asset> result;
	for (const auto& pair : m_register)
	{
		result.push_back(pair.second);
	}
	return result;
}

std::vector<Asset> AssetLibrary::list(const Asset::Type type) const
{
	std::vector<Asset> result;
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
	static const auto getAssetFilename = [](const std::filesystem::path& filename) -> std::string
	{
		return filename.string().substr(0, filename.string().length() - std::string(Asset::Extension).length());
	};

	const auto& it = m_cache.find(id);
	if (it != m_cache.end() && !it->second.isExpired())
	{
		return it->second.asset.lock();
	}

	std::filesystem::path filename;
	if (getRedirector(id, filename) == false)
	{
		return nullptr;
	}

	Asset descriptor = Asset::load(filename);
	std::shared_ptr<Asset> asset = create(descriptor, getAssetFilename(filename));
	m_cache.insert(std::make_pair(asset->id, Slot(asset)));
	return asset;
}

std::shared_ptr<Asset> AssetLibrary::create(const AssetDescriptor& descriptor, const std::filesystem::path& filename)
{
	static const auto load = [](const std::filesystem::path& filename) -> std::string
	{
		std::ostringstream buf;
		std::ifstream input(filename.c_str());
		buf << input.rdbuf();
		return buf.str();
	};

	if (!std::filesystem::exists(filename))
	{
		return nullptr;
	}

	switch (descriptor.type)
	{
	case Asset::Type::Image:
	{
		return std::make_shared<ImageAsset>(Image::load(filename), descriptor);
	}
	case Asset::Type::Prefab:
	{
		return std::make_shared<PrefabAsset>(Prefab::load(filename), descriptor);
	}
	case Asset::Type::Scene:
	{
		return std::make_shared<SceneAsset>(load(filename), descriptor);
	}
	case Asset::Type::Sprite:
	{
		return std::make_shared<SpriteAsset>(Sprite::load(filename), descriptor);
	}
	case Asset::Type::SpriteAnimation:
	{
		return std::make_shared<SpriteAnimationAsset>(SpriteAnimation::load(filename), descriptor);
	}
	case Asset::Type::Text:
	{
		return std::make_shared<TextAsset>(load(filename), descriptor);
	}
	default: return nullptr;
	}
}

bool AssetLibrary::getRedirector(const uuid& id, std::filesystem::path& filename) const
{
	const auto& it = m_register.find(id);
	if (it != m_register.end())
	{
		return filename = it->second.filename, true;
	}
	return false;
}