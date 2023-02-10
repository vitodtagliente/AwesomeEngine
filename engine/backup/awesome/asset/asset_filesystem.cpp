#include "asset_filesystem.h"

#include <awesome/core/string_util.h>

#include "asset_library.h"

bool AssetFilesystem::erase(const std::filesystem::path& path)
{
	const std::filesystem::path meta_path = path.string() + Asset::Extension;
	if (!std::filesystem::exists(path) || !std::filesystem::exists(meta_path))
	{
		return false;
	}

	AssetLibrary& library = AssetLibrary::instance();
	AssetDatabase& db = library.database;

	AssetRecord* const record = db.find(path);
	if (record == nullptr) return false;

	library.release(record->id);
	db.erase(record->id);
	
	return std::filesystem::remove(path)
		&& std::filesystem::remove(meta_path);
}

bool AssetFilesystem::move(const std::filesystem::path& from, const std::filesystem::path& to)
{
	const std::filesystem::path meta_path = from.string() + Asset::Extension;
	if (!std::filesystem::exists(from) || !std::filesystem::exists(meta_path))
	{
		return false;
	}

	AssetLibrary& library = AssetLibrary::instance();
	AssetDatabase& db = library.database;

	AssetRecord* const record = db.find(from);
	if (record == nullptr) return false;

	std::filesystem::rename(from, to);
	std::filesystem::rename(from.string() + Asset::Extension, to.string() + Asset::Extension);

	AssetPtr asset = library.find(record->id);
	if (asset != nullptr)
	{
		asset->path = to;
	}

	record->path = to;
	return true;
}

bool AssetFilesystem::rename(const std::filesystem::path& path, const std::string& name)
{
	static const auto renameAsset = [](const std::filesystem::path& filename, const std::string& renaming) -> std::filesystem::path
	{
		std::filesystem::path name = filename.stem();
		while (name.has_extension())
		{
			name = name.stem();
		}

		std::filesystem::path rename = renaming;
		while (rename.has_extension())
		{
			rename = rename.stem();
		}

		return StringUtil::replace(filename.string(), name.string(), rename.string());
	};

	const std::filesystem::path meta_path = path.string() + Asset::Extension;
	if (!std::filesystem::exists(path) || !std::filesystem::exists(meta_path))
	{
		return false;
	}

	AssetLibrary& library = AssetLibrary::instance();
	AssetDatabase& db = library.database;

	AssetRecord* const record = db.find(path);
	if (record == nullptr) return false;

	const std::filesystem::path new_name = renameAsset(path, name);

	std::filesystem::rename(path, new_name);
	std::filesystem::rename(meta_path, new_name.string() + Asset::Extension);

	AssetPtr asset = library.find(record->id);
	if (asset != nullptr)
	{
		asset->path = new_name;
	}

	record->path = new_name;
	return true;
}