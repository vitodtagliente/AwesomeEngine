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
			importFile(path);
		}
	}
}

void AssetImporter::import(const std::filesystem::path& path)
{
	import(path, false);
}

void AssetImporter::importDirectory(const std::filesystem::path& path, const bool recursive)
{
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (!entry.is_directory())
		{
			importFile(entry.path());
		}
		else if (entry.is_directory() && recursive)
		{
			importDirectory(entry.path(), recursive);
		}
	}
}

void AssetImporter::importFile(const std::filesystem::path& path)
{
	AssetLibrary& library = AssetLibrary::instance();

	if (Asset::isAsset(path))
	{
		const Asset::Descriptor descriptor = Asset::Descriptor::load(path);
		if (descriptor)
		{
			// The asset is already loaded
			if (library.find(descriptor.id)) return;

			library.insert(descriptor);
			return;
		}
		return;
	}

	const std::filesystem::path assetPath = path.string() + Asset::Extension;
	if (std::filesystem::exists(assetPath))
	{
		return;
	}

	const Asset::Type type = Asset::getTypeByExtension(path.extension().string());
	if (type != Asset::Type::None)
	{
		Asset::Descriptor descriptor(type);
		descriptor.save(assetPath);

		library.insert(descriptor);
	}
}