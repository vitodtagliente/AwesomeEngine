#include "asset_library.h"

#include <list>

AssetLibrary::AssetLibrary()
	: redirectors()
	, m_caches()
{

}

std::shared_ptr<Asset> AssetLibrary::find(const Asset::Type type, const uuid& id)
{
	AssetCache& cache = getCache(type);
	cache.update();

	std::shared_ptr<Asset> asset = cache.find(id);
	if (asset == nullptr)
	{
		std::string filename;
		if (getRedirector(id, filename))
		{
			asset = create(type, filename);
			if (asset)
			{
				cache.insert(asset);
			}
		}
	}
	return asset;
}

std::shared_ptr<Asset> AssetLibrary::find(const Asset::Type type, const std::string& filename)
{
	uuid id;
	if (getRedirector(filename, id))
	{
		return find(type, id);
	}
	else
	{
		AssetCache& cache = getCache(type);
		cache.update();

		std::shared_ptr<Asset> asset = create(type, filename);
		if (asset != nullptr)
		{
			redirectors.insert(std::make_pair(id, filename));
			cache.insert(asset);
		}
		return asset;
	}
}

AssetCache& AssetLibrary::getCache(const Asset::Type type)
{
	const auto& it = m_caches.find(type);
	if (it == m_caches.end())
	{
		return m_caches.insert(std::make_pair(type, AssetCache())).first->second;
	}
	return it->second;
}

std::shared_ptr<Asset> AssetLibrary::create(const Asset::Type type, const std::string& filename)
{
	switch (type)
	{
	case Asset::Type::Image:
	{
		return std::make_shared<ImageAsset>(Image::load(filename));
	}
	default: return nullptr;
	}
}

bool AssetLibrary::getRedirector(const uuid& id, std::string& filename) const
{
	const auto& it = redirectors.find(id);
	if (it != redirectors.end())
	{
		return filename = it->second, true;
	}
	return false;
}

bool AssetLibrary::getRedirector(const std::string& filename, uuid& id) const
{
	const auto& it = std::find_if(redirectors.begin(), redirectors.end(), [&filename](const std::pair<uuid, std::string>& pair) -> bool
		{
			return pair.second == filename;
		}
	);

	if (it != redirectors.end())
	{
		return id = it->first, true;
	}
	return false;
}

AssetCache::AssetCache()
	: m_assets()
{
}

void AssetCache::insert(const std::shared_ptr<Asset>& asset)
{
	m_assets.insert(std::make_pair(asset->id, Slot(asset)));
}

std::shared_ptr<Asset> AssetCache::find(const uuid& id) const
{
	const auto& it = m_assets.find(id);
	if (it != m_assets.end())
	{
		return it->second.asset;
	}
	return nullptr;
}

void AssetCache::update()
{
	std::list<uuid> assetsToRelease;

	for (const auto& pair : m_assets)
	{
		if (pair.second.asset.unique())
		{
			assetsToRelease.push_back(pair.first);
		}
	}

	for (const uuid& id : assetsToRelease)
	{
		m_assets.erase(id);
	}
}