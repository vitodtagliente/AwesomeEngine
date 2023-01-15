#include "common_asset_identifier.h"

#include <string>
#include <vector>

#include "image_asset.h"
#include "prefab_asset.h"
#include "scene_asset.h"
#include "sprite_animation_asset.h"
#include "text_asset.h"
#include "tileset_asset.h"

bool CommonAssetIdentifier::identify(const std::filesystem::path& path) const
{
	static std::vector<std::string> s_extensions{
		".png", ".jpg", ".jpeg", ".bmp",
		".prefab",
		".scene",
		".spriteanim",
		".txt", ".md", ".shader", ".ini", ".cfg",
		".tileset"
	};

	const std::string& extension = path.extension().string();
	return std::find(s_extensions.begin(), s_extensions.end(), extension) != s_extensions.end();
}

AssetPtr CommonAssetIdentifier::instatiate(const std::filesystem::path& path) const
{
	const std::string& extension = path.extension().string();
	if (extension == ".png" || extension == ".jpg" || extension == ".jpeg" || extension == ".bmp")
	{
		return std::make_shared<ImageAsset>();
	}
	if (extension == ".prefab")
	{
		return std::make_shared<PrefabAsset>();
	}
	if (extension == ".scene")
	{
		return std::make_shared<SceneAsset>();
	}
	if (extension == ".spriteanim")
	{
		return std::make_shared<SpriteAnimationAsset>();
	}
	if (extension == ".txt" || extension == ".md" || extension == ".shader" || extension == ".ini" || extension == ".cfg")
	{
		return std::make_shared<TextAsset>();
	}
	if (extension == ".tileset")
	{
		return std::make_shared<TilesetAsset>();
	}
	return nullptr;
}
