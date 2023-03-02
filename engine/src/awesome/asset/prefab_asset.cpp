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
		return Serializer<Entity>::deserialize(file, data.entity);
	}
	return false;
}

bool PrefabAsset::save(const std::filesystem::path& _path) const
{
	return JsonFile::save(Serializer<Entity>::serialize(data.entity), _path), true;
}
