#include "tileset_asset.h"

#include <awesome/data/json_file.h>

void TilesetAsset::load(const std::filesystem::path& path)
{
	JsonFile::load(path, data);
}