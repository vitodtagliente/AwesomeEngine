#include "asset_importer.h"

#include <string>

#include "asset.h"
#include "asset_library.h"

void AssetImporter::import(const std::filesystem::path& path, const bool recursive)
{
	if (std::filesystem::exists(path))
	{
		if (std::filesystem::is_directory(path))
		{
			importDirectory(path, recursive);
		}
		else
		{
			uuid id{ uuid::Invalid };
			importFile(path, id);
		}
	}
}

bool AssetImporter::import(const std::filesystem::path& path, uuid& id)
{
	return importFile(path, id);
}

bool AssetImporter::import(const std::filesystem::path& path)
{
	uuid id{ uuid::Invalid };
	return importFile(path, id);
}

void AssetImporter::importDirectory(const std::filesystem::path& path, const bool recursive)
{
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (!entry.is_directory())
		{
			uuid id{ uuid::Invalid };
			importFile(entry.path(), id);
		}
		else if (entry.is_directory() && recursive)
		{
			importDirectory(entry.path(), recursive);
		}
	}
}

bool AssetImporter::importFile(const std::filesystem::path& path, uuid& id)
{
	id = uuid::Invalid;
	AssetLibrary& library = AssetLibrary::instance();

	if (Asset::isAsset(path))
	{
		const Asset::Descriptor descriptor = Asset::Descriptor::load(path);
		if (descriptor)
		{
			// The asset is already loaded
			id = descriptor.id;
			if (library.find(descriptor.id)) return true;

			library.insert(descriptor);
			return true;
		}
		return false;
	}

	const std::filesystem::path assetPath = path.string() + Asset::Extension;
	if (std::filesystem::exists(assetPath))
	{
		return false;
	}

	const Asset::Type type = Asset::getTypeByExtension(path.extension().string());
	if (type == Asset::Type::None)
	{		
		return false;
	}

	Asset::Descriptor descriptor(type);
	descriptor.save(assetPath);

	id = descriptor.id;
	library.insert(descriptor);
	return true;
}