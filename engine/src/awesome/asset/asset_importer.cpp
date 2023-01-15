#include "asset_importer.h"

#include <string>
#include <vector>

#include <awesome/data/json_file.h>

#include "asset.h"
#include "asset_identifier.h"
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

	static std::vector<std::unique_ptr<AssetIdentifier>> s_identifiers;
	if (s_identifiers.empty())
	{
		const auto& types = TypeFactory::list("Type", "AssetIdentifier");
		for (const auto& type : types)
		{
			std::unique_ptr<AssetIdentifier> identifier(TypeFactory::instantiate<AssetIdentifier>(type));
			if (identifier != nullptr)
			{
				s_identifiers.push_back(std::move(identifier));
			}
		}
	}

	AssetPtr asset;
	const auto& it = std::find_if(s_identifiers.begin(), s_identifiers.end(),
		[&path](const std::unique_ptr<AssetIdentifier>& identifier) -> bool
		{
			return identifier->identify(path);
		}
	);

	if (it != s_identifiers.end())
	{
		asset = (*it)->instatiate(path);
		if (asset != nullptr)
		{
			db.insert(path, asset->getTypeName());
			return JsonFile::save(std::dynamic_pointer_cast<Type>(asset), assetPath), true;
		}
	}
	return false;
}