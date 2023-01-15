#include "sprite_animation_asset.h"

#include <awesome/data/json_file.h>

bool SpriteAnimationAsset::load(const std::filesystem::path& _path)
{
	return JsonFile::load(_path, data);
}

bool SpriteAnimationAsset::save(const std::filesystem::path& _path) const
{
	return JsonFile::save(data, _path), true;
}
