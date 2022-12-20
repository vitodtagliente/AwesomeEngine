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
		if (tileset->state != Asset::State::Ready)
		{
			return;
		}

		TilesetAsset::data_t& data = tileset->data.value();
		Layout::input("image", data.image);
		for (const auto& tile : data.tiles)
		{
			Layout::image(data.image, tile->rect, 32, 32);
		}

		if (Layout::collapsingHeader("Edit"))
		{
			Layout::image(data.image);
			Layout::input("Tile Size", data.tileSize);
			if (Layout::button("Generate") && data.image != nullptr)
			{
				data.tiles.clear();
				const int h = static_cast<float>(data.image->data->height) / data.tileSize.y;
				const int w = static_cast<float>(data.image->data->width) / data.tileSize.x;
				const float size_x = 1.f / data.tileSize.x;
				const float size_y = 1.f / data.tileSize.y;
				for (int j = 0; j < h; ++j)
				{
					for (int i = 0; i < w; ++i)
					{
						std::unique_ptr<Tile> tile = std::make_unique<Tile>();
						tile->rect.x = i * size_x;
						tile->rect.y = j * size_y;
						tile->rect.width = size_x;
						tile->rect.height = size_y;

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