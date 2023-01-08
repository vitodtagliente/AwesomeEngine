#include "sprite_animation_asset.h"

#include <awesome/data/json_file.h>

void SpriteAnimationAsset::load(const std::filesystem::path& path)
{
	JsonFile::load(path, data);
}