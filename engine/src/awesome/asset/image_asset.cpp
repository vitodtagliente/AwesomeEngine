#include "image_asset.h"

void ImageAsset::load(const std::filesystem::path& path)
{
	data = Image::load(path);
}