#include "prefab_asset.h"

#include <awesome/data/json_file.h>

bool PrefabAsset::load(const std::filesystem::path& _path)
{
	return JsonFile::load(_path, data);
}

bool PrefabAsset::save(const std::filesystem::path& _path) const
{
	return JsonFile::save(data, _path), true;
}
