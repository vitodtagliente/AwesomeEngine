#include "asset_importer.h"

#include <string>

#include <awesome/core/string_util.h>
#include <awesome/data/json_file.h>

#include "asset.h"
#include "asset_library.h"

bool AssetImporter::import(const std::filesystem::path& path, const bool recursive, bool& newFilesFound)
{
	newFilesFound = false;

	bool result = true;
	if (std::filesystem::exists(path))
	{
		if (std::filesystem::is_directory(path))
		{
			result &= importDirectory(path, recursive, newFilesFound);
		}
		else
		{
			result &= importFile(path, newFilesFound);
		}
	}
	return result;
}

bool AssetImporter::import(const std::filesystem::path& path, bool& newFilesFound)
{
	return importFile(path, newFilesFound);
}

bool AssetImporter::importDirectory(const std::filesystem::path& path, const bool recursive, bool& newFilesFound)
{
	bool result = true;
	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (!entry.is_directory())
		{
			result &= importFile(entry.path(), newFilesFound);
		}
		else if (entry.is_directory() && recursive)
		{
			result &= importDirectory(entry.path(), recursive, newFilesFound);
		}
	}
	return result;
}

bool AssetImporter::importFile(const std::filesystem::path& path, bool& newFilesFound)
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

	int assetType = AssetType_Invalid;
	if (!Asset::isSupported(path, assetType))
	{
		return false;
	}

	AssetRecord record;
	record.path = path;
	record.type = assetType;
	record.save(assetPath);

	db.insert(record);
	newFilesFound = true;

	return true;
}