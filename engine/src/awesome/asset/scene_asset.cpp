#include "scene_asset.h"

#include <awesome/data/type_file.h>

SceneAsset::SceneAsset()
	: Asset()
{
	type = AssetType_Scene;
}

bool SceneAsset::load(const std::filesystem::path& _path)
{
	return TypeFile::load(_path, data);
}

bool SceneAsset::save(const std::filesystem::path& _path) const
{
	return TypeFile::save(data, _path), true;
}
