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

		TilesetAsset::data_t& data = tileset->data.value();
		Layout::input("image", data.image);
		for (const auto& tile : data.tiles)
		{
			Layout::image(data.image, tile->rect, data.tileSize.x, data.tileSize.y);
		}

		if (Layout::collapsingHeader("Edit"))
		{
			Layout::image(data.image);
			Layout::input("Tile Size", data.tileSize);
			if (Layout::button("Generate") && data.image != nullptr)
			{
				data.tiles.clear();
				const int h = static_cast<int>(data.image->data->height / data.tileSize.y);
				const int w = static_cast<int>(data.image->data->width / data.tileSize.x);
				for (int j = 0; j < h; ++j)
				{
					for (int i = 0; i < w; ++i)
					{
						std::unique_ptr<Tile> tile = std::make_unique<Tile>();
						tile->rect.x = static_cast<float>(i) * data.tileSize.x;
						tile->rect.y = static_cast<float>(j) * data.tileSize.y;
						tile->rect.width = data.tileSize.x;
						tile->rect.height = data.tileSize.y;

						data.tiles.push_back(std::move(tile));
					}
				}
			}
		}		

		Layout::separator();

		if (Layout::button(TextIcon::save(" Save")))
		{
			JsonFile::save(tileset->data.value(), tileset->descriptor.getDataPath());
		}
	}
}