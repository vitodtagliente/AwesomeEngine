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
		for (size_t i = 0; i < data.tiles.size(); ++i)
		{
			const std::string context = "[tile-" + std::to_string(i) + "]";
			Layout::beginContext(context);
			if (Layout::collapsingHeader(context))
			{
				Layout::input("Rect", data.tiles[i]->rect);
				Layout::image(data.image, data.tiles[i]->rect);
			}
			Layout::endContext();
		}

		if (Layout::collapsingHeader("Edit"))
		{
			Layout::image(data.image);
			Layout::input("Tile Size", data.tileSize);
			if (Layout::button("Generate") && data.image != nullptr)
			{
				data.tiles.clear();
				const int w = data.image->data->width / static_cast<int>(data.tileSize.x);
				const int h = data.image->data->height / static_cast<int>(data.tileSize.y);
				const float size_x = 1.f / static_cast<float>(w);
				const float size_y = 1.f / static_cast<float>(h);
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