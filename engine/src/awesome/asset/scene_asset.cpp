#include "scene_asset.h"

#include <awesome/data/json_file.h>

void SceneAsset::load(const std::filesystem::path& path)
{
	JsonFile::load(path, data);
}