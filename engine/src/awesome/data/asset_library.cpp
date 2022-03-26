#include "asset_library.h"

#include <filesystem>
#include <fstream>
#include <list>

AssetLibrary::AssetLibrary()
	: redirectors()
	, m_assets()
	, m_directory(std::filesystem::current_path().string() + "/../assets")
{

}

std::shared_ptr<Asset> AssetLibrary::find(const uuid& id)
{
	const auto& it = m_assets.find(id);
	if (it == m_assets.end())
	{
		std::string filename;
		if (getRedirector(id, filename) == false)
		{
			return nullptr;
		}

		Asset descriptor = Asset::load(filename);
		std::shared_ptr<Asset> asset = create(descriptor, filename.substr(0, filename.length() - std::string(Asset::Extension).length()));
		m_assets.insert(std::make_pair(asset->id, Slot(asset)));
		return asset;
	}
	else
	{
		return it->second.asset;
	}
}

std::shared_ptr<Asset> AssetLibrary::create(const Asset& descriptor, const std::string& filename)
{
	static const auto read = [](const std::string& filename) -> std::string
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
		const std::filesystem::path file(filename);
		if (std::filesystem::exists(file))
		{
			return std::make_shared<PrefabAsset>(read(filename), descriptor);
		}
		return nullptr;
		break;
	}
	case Asset::Type::Text:
	{	
		const std::filesystem::path file(filename);
		if (std::filesystem::exists(file))
		{
			return std::make_shared<TextAsset>(read(filename), descriptor);
		}
		return nullptr;
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