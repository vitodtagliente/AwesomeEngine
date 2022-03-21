#include "asset_importer.h"

#include <filesystem>
#include <map>
#include <string>
#include <vector>

#include <awesome/data/archive.h>
#include <awesome/data/asset_library.h>
#include <awesome/encoding/json.h>

#include "file.h"

namespace editor
{
	std::map<Asset::Type, std::set<std::string>> AssetImporter::s_filetypes{
		{ Asset::Type::Image, {".png", ".jpg", ".jpeg", ".bmp"}},
		{ Asset::Type::Text, {".txt", ".md", ".shader", ".ini"}}
	};

	AssetImporter::AssetImporter()
	{

	}

	void AssetImporter::import(const std::string& directory, const bool recursive)
	{
		std::vector<File> files;

		const std::filesystem::path currentPath(directory);
		for (const auto& entry : std::filesystem::directory_iterator(currentPath))
		{
			files.push_back(File(entry.path()));
		}

		AssetLibrary* const library = AssetLibrary::instance();
		for (const File& file : files)
		{
			if (file.extension == ".asset")
			{

			}
			else
			{
				const auto& it = std::find_if(files.begin(), files.end(), [&file](const File& other) -> bool
					{
						return other.name == file.name && other.extension == ".asset";
					}
				);

				if (it != files.end())
				{
					files.erase(it);
				}
				else
				{
					const Asset::Type type = getTypeByExtension(file.extension);
					if (type != Asset::Type::None)
					{
						Archive archive(directory + "/" + file.name + ".asset", Archive::Mode::Write);
						Asset asset(type);
						archive << json::Serializer::to_string(asset.serialize());
					}
				}
			}
		}
	}

	Asset::Type AssetImporter::getTypeByExtension(const std::string& ext) const
	{
		for (const auto& pair : s_filetypes)
		{
			if (pair.second.find(ext) != pair.second.end())
			{
				return pair.first;
			}
		}
		return Asset::Type::None;
	}
}