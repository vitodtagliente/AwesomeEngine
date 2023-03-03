#include "prefab_asset.h"

#include <awesome/data/json_file.h>
#include <awesome/serialization/entity_serialization.h>

PrefabAsset::PrefabAsset()
	: Asset()
{
	type = AssetType_Prefab;
}

bool PrefabAsset::load(const std::filesystem::path& _path)
{
	json::value file;
	if (JsonFile::load(_path, file))
	{
		return file >> data.entity, true;
	}
	return false;
}

bool PrefabAsset::save(const std::filesystem::path& _path) const
{
	json::value file;
	file << data.entity;
	return JsonFile::save(file, _path), true;
}
