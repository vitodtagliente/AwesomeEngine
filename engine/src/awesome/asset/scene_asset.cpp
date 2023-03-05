#include "scene_asset.h"

#include <awesome/core/serialization.h>
#include <awesome/data/json_file.h>

SceneAsset::SceneAsset()
	: Asset()
{
	type = AssetType_Scene;
}

bool SceneAsset::load(const std::filesystem::path& _path)
{
	json::value file;
	if (JsonFile::load(_path, file))
	{
		return file >> data.entities, true;
	}
	return false;
}

bool SceneAsset::save(const std::filesystem::path& _path) const
{
	json::value file;
	file << data.entities;
	return JsonFile::save(file, _path), true;
}
