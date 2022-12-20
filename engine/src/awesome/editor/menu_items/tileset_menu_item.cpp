#include "tileset_menu_item.h"

#include <awesome/asset/asset_importer.h>
#include <awesome/asset/tileset_asset.h>
#include <awesome/data/json_file.h>
#include <awesome/editor/dialog.h>

void TilesetMenuItem::execute()
{
	Dialog::instance().save("Save Tileset...", Asset::getExtensionByType(Asset::Type::Tileset), [](const std::filesystem::path& filename) -> void
		{
			if (!filename.string().empty())
			{
				TilesetAsset::data_t tileset;
				JsonFile::save(tileset, filename);

				AssetImporter importer;
				importer.import(filename);
			}
		}
	);
}