#include "scene_asset.h"

#include <awesome/data/json_file.h>
#include <awesome/serialization/entity_serialization.h>

SceneAsset::SceneAsset()
	: Asset()
{
	type = AssetType_Scene;
}

bool SceneAsset::load(const std::filesystem::path& _path)
{
	return false;
}

bool SceneAsset::save(const std::filesystem::path& _path) const
{
	return JsonFile::save(Serializer<std::vector<Entity>>::serialize(data.entities), _path), true;
}
