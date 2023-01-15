#include "tileset_asset.h"

#include <awesome/data/json_file.h>

bool TilesetAsset::load(const std::filesystem::path& _path)
{
	return JsonFile::load(_path, data);
}

bool TilesetAsset::save(const std::filesystem::path& _path) const
{
	return JsonFile::save(data, _path), true;
}
