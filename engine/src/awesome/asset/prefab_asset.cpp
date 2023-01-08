#include "prefab_asset.h"

#include <awesome/data/json_file.h>

void PrefabAsset::load(const std::filesystem::path& path)
{
	JsonFile::load(path, data);
}