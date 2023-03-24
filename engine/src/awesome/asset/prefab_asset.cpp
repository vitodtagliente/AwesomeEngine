#include "prefab_asset.h"

#include <awesome/data/text_file.h>

PrefabAsset::PrefabAsset()
	: Asset()
{
	type = AssetType_Prefab;
}

bool PrefabAsset::load(const std::filesystem::path& _path)
{
	std::string content;
	if (TextFile::load(_path, content))
	{
		data.from_json(content);
		return true;
	}
	return false;
}

bool PrefabAsset::save(const std::filesystem::path& _path) const
{
	TextFile::save(data.to_json(), _path);
	return true;
}
