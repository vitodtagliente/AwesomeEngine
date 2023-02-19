#include "scene_asset.h"

#include <awesome/data/json_file.h>
#include <awesome/serialization/entity_serialization.h>

bool SceneAsset::load(const std::filesystem::path& _path)
{
	return false;
}

bool SceneAsset::save(const std::filesystem::path& _path) const
{
	return JsonFile::save(serialize(data.entities), _path), true;
}