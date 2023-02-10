#include "asset.h"

#include "asset_library.h"

bool Asset::operator==(const Asset& other) const
{
	return id == other.id;
}

bool Asset::operator!=(const Asset& other) const
{
	return id != other.id;
}

bool Asset::isSupported(const std::filesystem::path& path)
{
	const auto& handlers = AssetLibrary::instance().handlers();
	const auto& it = std::find_if(
		handlers.begin(),
		handlers.end(),
		[extension = path.extension().string()](const AssetHandler& handler) -> bool
		{
			return std::find(handler.extensions.begin(), handler.extensions.end(), extension) != handler.extensions.end();
		}
	);
	return it != handlers.end();
}

bool Asset::isSupported(const std::filesystem::path& path, int& type)
{
	const auto& handlers = AssetLibrary::instance().handlers();
	const auto& it = std::find_if(
		handlers.begin(),
		handlers.end(),
		[extension = path.extension().string()](const AssetHandler& handler) -> bool
		{
			return std::find(handler.extensions.begin(), handler.extensions.end(), extension) != handler.extensions.end();
		}
	);

	type = AssetType_Invalid;
	if (it != handlers.end())
	{
		type = it->type;
	}
	return false;
}
