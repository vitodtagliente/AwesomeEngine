#include "scene_asset.h"

#include <awesome/data/text_file.h>

SceneAsset::SceneAsset()
	: Asset()
{
	type = AssetType_Scene;
}

bool SceneAsset::load(const std::filesystem::path& _path)
{
	std::string content;
	if (TextFile::load(_path, content))
	{
		data.from_json(content);
		return true;
	}
	return false;
}

bool SceneAsset::save(const std::filesystem::path& _path) const
{
	TextFile::save(data.to_json(), _path);
	return true;
}
