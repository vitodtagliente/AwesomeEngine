#include "asset_library.h"

AssetLibrary::AssetLibrary()
	: redirectors()
	, m_caches()
{
}

Asset* const AssetLibrary::find(const Asset::Type type, const uuid& id)
{
	AssetCache& cache = getCache(type);
	Asset* asset = cache.find(id);
	if (asset == nullptr)
	{
		std::string filename;
		if (getRedirector(id, filename))
		{
			asset = create(type, filename);
		}
	}
	return asset;
}

Asset* const AssetLibrary::find(const Asset::Type type, const std::string& filename)
{
	uuid id;
	if (getRedirector(filename, id))
	{
		return find(type, id);
	}
	else
	{
		redirectors.insert(std::make_pair(id, filename));
		return create(type, filename);
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

Asset* const AssetLibrary::create(const Asset::Type type, const std::string& filename)
{
	return nullptr;
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

void AssetCache::insert(Asset* const asset)
{
	m_assets.insert(std::make_pair(asset->getId(), Slot(asset)));
}

Asset* const AssetCache::find(const uuid& id) const
{
	const auto& it = m_assets.find(id);
	if (it != m_assets.end())
	{
		return it->second.asset;
	}
	return nullptr;
}

void AssetCache::free(const uuid& id)
{
	const auto& it = m_assets.find(id);
	if (it != m_assets.end())
	{
		delete it->second.asset;
		m_assets.erase(it);
	}
}
