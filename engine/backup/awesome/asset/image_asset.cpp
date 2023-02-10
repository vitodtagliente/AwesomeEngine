#include "image_asset.h"

bool ImageAsset::load(const std::filesystem::path& _path)
{
	return data = Image::load(_path), true;
}

bool ImageAsset::save(const std::filesystem::path&) const
{
	return false;
}
