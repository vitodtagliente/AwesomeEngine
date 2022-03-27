#include "asset_library.h"

#include <filesystem>
#include <fstream>
#include <list>

AssetLibrary::AssetLibrary()
	: m_cachedAssets()
	, m_assetDescriptors()
	, m_directory(std::filesystem::current_path().string() + "/../assets")
{

}

void AssetLibrary::registerDescriptor(const Asset& descriptor)
{
	m_assetDescriptors.insert(std::make_pair(descriptor.id, descriptor));
}

std::vector<Asset> AssetLibrary::list() const
{
	std::vector<Asset> result;
	for (const auto& pair : m_assetDescriptors)
	{
		result.push_back(pair.second);
	}
	return result;
}

std::vector<Asset> AssetLibrary::list(const Asset::Type type) const
{
	std::vector<Asset> result;
	for (const auto& pair : m_assetDescriptors)
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

	const auto& it = m_cachedAssets.find(id);
	if (it == m_cachedAssets.end())
	{
		std::filesystem::path filename;
		if (getRedirector(id, filename) == false)
		{
			return nullptr;
		}

		Asset descriptor = Asset::load(filename);
		std::shared_ptr<Asset> asset = create(descriptor, getAssetFilename(filename));
		m_cachedAssets.insert(std::make_pair(asset->id, Slot(asset)));
		return asset;
	}
	else
	{
		return it->second.asset;
	}
}

std::shared_ptr<Asset> AssetLibrary::create(const Asset& descriptor, const std::filesystem::path& filename)
{
	static const auto read = [](const std::filesystem::path& filename) -> std::string
	{
		std::ostringstream buf;
		std::ifstream input(filename.c_str());
		buf << input.rdbuf();
		return buf.str();
	};

	switch (descriptor.type)
	{
	case Asset::Type::Image:
	{
		return std::make_shared<ImageAsset>(Image::load(filename), descriptor);
	}
	case Asset::Type::Prefab:
	{
		if (std::filesystem::exists(filename))
		{
			return std::make_shared<PrefabAsset>(read(filename), descriptor);
		}
		return nullptr;
		break;
	}
	case Asset::Type::Text:
	{
		if (std::filesystem::exists(filename))
		{
			return std::make_shared<TextAsset>(read(filename), descriptor);
		}
		return nullptr;
	}
	default: return nullptr;
	}
}

bool AssetLibrary::getRedirector(const uuid& id, std::filesystem::path& filename) const
{
	const auto& it = m_assetDescriptors.find(id);
	if (it != m_assetDescriptors.end())
	{		
		return filename = it->second.filename, true;
	}
	return false;
}