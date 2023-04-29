#include "asset.h"

#include "asset_library.h"

Asset& Asset::operator=(const Asset& other)
{
	if (type == other.type)
	{
		id = other.id;
		path = other.path;
		state = State::None;
	}
	return *this;
}

Asset& Asset::operator=(const AssetRecord& other)
{
	if (type == other.type)
	{
		id = other.id;
		path = other.path;
		state = State::None;
	}
	return *this;
}

bool Asset::operator==(const Asset& other) const
{
	return id == other.id;
}

bool Asset::operator!=(const Asset& other) const
{
	return id != other.id;
}

const AssetRecord* const Asset::find(const uuid& id)
{
	return AssetLibrary::instance().database.find(id);
}

const std::vector<std::string>& Asset::extensions(const int type)
{
	const auto& loaders = AssetLibrary::instance().loaders();
	const auto& it = std::find_if(
		loaders.begin(),
		loaders.end(),
		[type](const std::unique_ptr<AssetLoader>& loader) -> bool
		{
			return loader->type == type;
		}
	);
	
	if (it != loaders.end())
	{
		return (*it)->extensions;
	}

	static std::vector<std::string> s_extensions;
	return s_extensions;
}

bool Asset::isSupported(const std::filesystem::path& path)
{
	const auto& loaders = AssetLibrary::instance().loaders();
	const auto& it = std::find_if(
		loaders.begin(),
		loaders.end(),
		[extension = path.extension().string()](const std::unique_ptr<AssetLoader>& loader) -> bool
		{
			const auto& extensions = loader->extensions;
			return std::find(extensions.begin(), extensions.end(), extension) != extensions.end();
		}
	);
	return it != loaders.end();
}

bool Asset::isSupported(const std::filesystem::path& path, int& type)
{
	const auto& loaders = AssetLibrary::instance().loaders();
	const auto& it = std::find_if(
		loaders.begin(),
		loaders.end(),
		[extension = path.extension().string()](const std::unique_ptr<AssetLoader>& loader) -> bool
		{
			const auto& extensions = loader->extensions;
			return std::find(extensions.begin(), extensions.end(), extension) != extensions.end();
		}
	);
	
	type = AssetType_Invalid;
	if (it != loaders.end())
	{
		type = (*it)->type;
		return true;
	}
	return false;
}
