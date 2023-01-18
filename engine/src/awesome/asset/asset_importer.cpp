#include "asset_importer.h"

#include <string>
#include <vector>

#include <awesome/core/string_util.h>
#include <awesome/data/json_file.h>

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

bool AssetImporter::import(const std::filesystem::path& path)
{
	return importFile(path);
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

bool AssetImporter::importFile(const std::filesystem::path& path)
{
	AssetDatabase& db = AssetLibrary::instance().database;

	static const auto& isAsset = [](const std::filesystem::path& path) -> bool
	{
		return path.extension().string() == Asset::Extension;
	};

	if (isAsset(path)) return true;

	const std::filesystem::path assetPath = path.string() + Asset::Extension;
	if (std::filesystem::exists(assetPath))
	{
		// the asset should be already loaded into the database
		return db.find(path) == nullptr;
	}

	const auto& asset_types = TypeFactory::list("Type", "Asset");
	const std::string ext = path.extension().string();
	const auto& it = std::find_if(asset_types.begin(), asset_types.end(),
		[&ext](const TypeDefinition& type) -> bool
		{
			const auto& it = type.meta.find("Extension");
			if(it != type.meta.end())
			{
				return StringUtil::contains(it->second, ext, StringUtil::CompareMode::IgnoreCase);
			}
			return false;
		}
	);

	if (it != asset_types.end())
	{
		AssetPtr asset = std::shared_ptr<Asset>(TypeFactory::instantiate<Asset>(it->name));
		if (asset != nullptr)
		{
			db.insert(path, asset->getTypeName());
			return JsonFile::save(*asset, assetPath), true;
		}
	}
	return false;
}