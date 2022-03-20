#include "content_browser.h"

#include <filesystem>

#include <imgui.h>

#include <awesome/data/archive.h>
#include <awesome/data/asset_library.h>
#include <awesome/encoding/json.h>
#include <awesome/entity/entity.h>

#include "../context.h"

namespace editor
{
	ContentBrowser::ContentBrowser()
		: Window()
		, m_dir(AssetLibrary::instance()->getDirectory())
	{
	}

	std::string ContentBrowser::getTitle() const
	{
		return "Content Browser";
	}

	void ContentBrowser::render(Context& context)
	{
		if (context.button(".."))
		{
			m_dir = Dir(m_dir.parent);
			return;
		}

		for (const File& file : m_dir.files)
		{
			if (context.button(file.name))
			{
				if (file.isDirectory)
				{
					m_dir = Dir(m_dir.path + "/" + file.name);
					return;
				}
				else
				{
					// TODO
				}
			}
		}
	}

	ContentBrowser::Dir::Dir(const std::string& directory)
		: path(directory)
		, parent()
		, files()
	{
		const std::filesystem::path currentPath(directory);
		parent = currentPath.parent_path().string();
		for (const auto& entry : std::filesystem::directory_iterator(currentPath))
		{
			const std::string filename = entry.path().filename().string();
			files.push_back(File(filename, entry.is_directory()));
		}
	}

	ContentBrowser::File::File(const std::string& name, const bool isDirectory)
		: name(name)
		, isDirectory(isDirectory)
	{
	}
}