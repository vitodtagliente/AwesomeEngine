#include "image_asset_handler.h"

#include <awesome/asset/image_asset.h>

ImageAssetHandler::ImageAssetHandler()
	: AssetHandler()
{
	create = []() ->AssetPtr { return std::make_shared<ImageAsset>(); };
	extensions = { ".png", ".bmp", ".jpg", ".jpeg" };
	name = "ImageAsset";
	type = AssetType_Image;
}
