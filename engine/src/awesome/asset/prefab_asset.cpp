#include "prefab_asset.h"

#include <awesome/data/type_file.h>

PrefabAsset::PrefabAsset()
	: Asset()
{
	type = AssetType_Prefab;
}

bool PrefabAsset::load(const std::filesystem::path& _path)
{
	return TypeFile::load(_path, data);
}

bool PrefabAsset::save(const std::filesystem::path& _path) const
{
	return TypeFile::save(data, _path), true;
}
