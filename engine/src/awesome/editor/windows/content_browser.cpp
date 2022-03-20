#include "content_browser.h"

#include <filesystem>

#include <imgui.h>

#include <awesome/data/archive.h>
#include <awesome/data/asset_library.h>
#include <awesome/encoding/json.h>
#include <awesome/entity/entity.h>

#include "../context.h"
#include "../selection_system.h"

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
		if (context.selectable("..", false))
		{
			m_dir = Dir(m_dir.parent);
			return;
		}

		SelectionSystem* selectionSystem = SelectionSystem::instance();
		const auto& selection = selectionSystem->getSelection();

		for (const File& file : m_dir.files)
		{
			if (context.selectable(file.name, selection.has_value() &&
				selection->type == SelectionSystem::Selection::Type::File && std::get<File>(selection->data) == file))
			{
				if (file.isDirectory)
				{
					m_dir = Dir(m_dir.path + "/" + file.name);
					SelectionSystem::instance()->unselect();
					return;
				}
				else
				{
					SelectionSystem::instance()->select(file);
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
			files.push_back(File(entry.path()));
		}
	}
}