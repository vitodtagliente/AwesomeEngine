#include "content_browser.h"

#include <filesystem>

#include <awesome/data/archive.h>
#include <awesome/data/asset_library.h>
#include <awesome/editor/context.h>
#include <awesome/editor/selection_system.h>
#include <awesome/encoding/json.h>
#include <awesome/entity/entity.h>

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

		for (const std::filesystem::path& file : m_dir.files)
		{
			if (context.selectable(file.filename().string(),
				// selection.has_value() &&
				// selection->type == SelectionSystem::Selection::Type::File && std::get<std::filesystem::path>(selection->data) == file))
				false))
			{
				// is directory
				if (!file.has_extension())
				{
					m_dir = Dir(file);
					SelectionSystem::instance()->unselect();
					return;
				}
				else
				{
					Asset descriptor = Asset::load(file.string());
					std::shared_ptr<Asset> asset = AssetLibrary::instance()->find(descriptor.id);
					if (asset)
					{
						SelectionSystem::instance()->select(asset);
					}
					else
					{
						SelectionSystem::instance()->unselect();
					}
				}
			}
		}
	}

	ContentBrowser::Dir::Dir(const std::string& directory)
		: path(std::filesystem::path(directory))
		, parent()
		, files()
	{
		parent = path.parent_path();
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			const std::filesystem::path& file = entry.path();
			if (file.extension().string() == s_assetExtension || entry.is_directory())
			{
				files.push_back(file);
			}
		}
	}

	ContentBrowser::Dir::Dir(const std::filesystem::path& path)
		: path(path)
		, parent(path.parent_path())
		, files()
	{
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			const std::filesystem::path& file = entry.path();
			if (file.extension().string() == s_assetExtension || entry.is_directory())
			{
				files.push_back(file);
			}
		}
	}
}