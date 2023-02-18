#include "prefab_asset.h"

#include <awesome/data/json_file.h>
#include <awesome/serialization/entity_serialization.h>

bool PrefabAsset::load(const std::filesystem::path& _path)
{
	return false;
}

bool PrefabAsset::save(const std::filesystem::path& _path) const
{
	return JsonFile::save(serialize(data.entity), _path), true;
}
