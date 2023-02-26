#include "image_asset.h"

ImageAsset::ImageAsset()
	: Asset()
{
	type = AssetType_Image;
}

bool ImageAsset::load(const std::filesystem::path& _path)
{
	return data = Image::load(_path), true;
}

bool ImageAsset::save(const std::filesystem::path&) const
{
	return false;
}
