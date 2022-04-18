#include "dir.h"

#include <awesome/data/asset.h>

namespace editor
{
	Dir::Dir(const std::filesystem::path& path)
		: files()
		, parent(path.parent_path())
		, path(path)
	{
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			const std::filesystem::path& file = entry.path();
			if (Asset::isAsset(file) || entry.is_directory())
			{
				files.push_back(file);
			}
		}
	}
}