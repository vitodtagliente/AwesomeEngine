#include "loader.h"

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
	Loader::Loader()
	{
		load();
	}

	void Loader::load()
	{
		std::vector<File> files;

		const std::string& directory = AssetLibrary::instance()->getDirectory();
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
					Archive archive(directory + "/" + file.name + ".asset", Archive::Mode::Write);

				}
			}
		}
	}
}