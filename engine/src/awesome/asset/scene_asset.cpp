#include "scene_asset.h"

#include <awesome/data/json_file.h>

bool SceneAsset::load(const std::filesystem::path& _path)
{
	return JsonFile::load(_path, data);
}

bool SceneAsset::save(const std::filesystem::path& _path) const
{
	return JsonFile::save(data, _path), true;
}