#include "asset.h"

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

const std::vector<std::string>& Asset::extensions(const int type)
{
	// const auto& handlers = AssetLibrary::instance().handlers();
	// const auto& it = std::find_if(
	// 	handlers.begin(),
	// 	handlers.end(),
	// 	[type](const AssetHandler& handler) -> bool
	// 	{
	// 		return handler.type == type;
	// 	}
	// );
	// 
	// if (it != handlers.end())
	// {
	// 	return it->extensions;
	// }

	static std::vector<std::string> s_extensions;
	return s_extensions;
}

bool Asset::isSupported(const std::filesystem::path& path)
{
	// const auto& handlers = AssetLibrary::instance().handlers();
	// const auto& it = std::find_if(
	// 	handlers.begin(),
	// 	handlers.end(),
	// 	[extension = path.extension().string()](const AssetHandler& handler) -> bool
	// 	{
	// 		return std::find(handler.extensions.begin(), handler.extensions.end(), extension) != handler.extensions.end();
	// 	}
	// );
	// return it != handlers.end();
	return false;
}

bool Asset::isSupported(const std::filesystem::path& path, int& type)
{
	// const auto& handlers = AssetLibrary::instance().handlers();
	// const auto& it = std::find_if(
	// 	handlers.begin(),
	// 	handlers.end(),
	// 	[extension = path.extension().string()](const AssetHandler& handler) -> bool
	// 	{
	// 		return std::find(handler.extensions.begin(), handler.extensions.end(), extension) != handler.extensions.end();
	// 	}
	// );
	// 
	// type = AssetType_Invalid;
	// if (it != handlers.end())
	// {
	// 	type = it->type;
	// 	return true;
	// }
	return false;
}
