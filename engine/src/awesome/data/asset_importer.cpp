#include "asset_importer.h"

#include <awesome/data/archive.h>
#include <awesome/data/asset_library.h>
#include <awesome/encoding/json.h>

void AssetImporter::import(const std::filesystem::path& directory, const bool recursive)
{
	for (const auto& entry : std::filesystem::directory_iterator(directory))
	{
		if (entry.is_directory() && recursive)
		{
			import(entry.path(), recursive);
			continue;
		}

		const std::filesystem::path& file = entry.path();
		import(file);
	}
}

bool AssetImporter::import(const std::filesystem::path& filename)
{
	if (!std::filesystem::exists(filename) || std::filesystem::is_directory(filename))
	{
		return false;
	}

	AssetLibrary& library = AssetLibrary::instance();

	if (Asset::isAsset(filename))
	{
		Asset descriptor = Asset::load(filename);
		if (descriptor)
		{
			// The asset is already loaded
			if (library.find(descriptor.id)) return true;

			library.insert(descriptor);
			return true;
		}
		return false;
	}

	const std::string assetFilename = filename.string() + Asset::Extension;
	if (std::filesystem::exists(assetFilename))
	{
		return true;
	}

	const Asset::Type type = Asset::getTypeByExtension(filename.extension().string());
	if (type != Asset::Type::None)
	{
		Archive archive(assetFilename, Archive::Mode::Write);
		Asset asset(type);
		asset.filename = assetFilename;
		archive << json::Serializer::to_string(asset.serialize());

		library.insert(asset);
	}

	return true;
}