#include "asset_importer.h"

#include <awesome/data/asset.h>
#include <awesome/data/asset_library.h>

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
		const Asset::Descriptor descriptor = Asset::Descriptor::load(filename);
		if (descriptor)
		{
			// The asset is already loaded
			if (library.find(descriptor.id)) return true;

			library.insert(descriptor);
			return true;
		}
		return false;
	}

	const std::filesystem::path path = filename.string() + Asset::Extension;
	if (std::filesystem::exists(path))
	{
		return true;
	}

	const Asset::Type type = Asset::getTypeByExtension(filename.extension().string());
	if (type != Asset::Type::None)
	{
		Asset::Descriptor descriptor(type);
		descriptor.save(path);

		library.insert(descriptor);
	}

	return true;
}