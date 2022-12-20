#include "tileset_inspector.h"

#include <awesome/asset/tileset_asset.h>
#include <awesome/data/json_file.h>
#include <awesome/editor/layout.h>

namespace editor
{
	bool TilesetInspector::canInspect(const AssetPtr& asset)
	{
		return asset->descriptor.type == Asset::Type::Tileset;
	}

	void TilesetInspector::inspect(const AssetPtr& asset)
	{
		TilesetAssetPtr tileset = std::static_pointer_cast<TilesetAsset>(asset);
		if (tileset == nullptr)
		{
			return;
		}

		Layout::input(tileset->data.value());

		Layout::separator();

		if (Layout::button(TextIcon::save(" Save")))
		{
			JsonFile::save(tileset->data.value(), tileset->descriptor.getDataPath());
		}
	}
}