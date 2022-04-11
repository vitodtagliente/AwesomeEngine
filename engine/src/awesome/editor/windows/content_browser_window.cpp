#include "content_browser_window.h"

#include <awesome/data/archive.h>
#include <awesome/data/asset_library.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/entity.h>

namespace editor
{
	ContentBrowserWindow::ContentBrowserWindow()
		: Window()
		, m_contentPath(getState()->workPath)
		, m_dir(m_contentPath)
		, m_newFolderName()
	{

	}

	void ContentBrowserWindow::render()
	{
		const auto& selection = getState()->selection;

		Layout::input("Folder", m_newFolderName);
		Layout::sameLine();
		if (Layout::button("New Folder") && !m_newFolderName.empty())
		{
			std::filesystem::create_directory(m_dir.path / m_newFolderName);
			m_newFolderName.clear();
		}

		if (selection.has_value())
		{
			Layout::sameLine();
			if (Layout::button("Delete"))
			{

			}
		}

		Layout::separator();

		if (m_contentPath != m_dir.path && Layout::selectable("..", false))
		{
			m_dir = Dir(m_dir.parent);
			getState()->workPath = m_dir.parent;
			return;
		}

		for (const std::filesystem::path& file : m_dir.files)
		{
			if (Layout::selectable(file.stem().string(),
				selection.has_value()
				&& selection->type == State::Selection::Type::Asset
				&& selection->asAsset()->filename == file.string()))
			{
				// is directory
				if (!file.has_extension())
				{
					m_dir = Dir(file);
					getState()->workPath = m_dir.path;
					return;
				}
				else
				{
					Asset descriptor = Asset::load(file.string());
					std::shared_ptr<Asset> asset = AssetLibrary::instance()->find(descriptor.id);
					if (asset)
					{
						getState()->select(asset);
					}
					else
					{
						getState()->select();
					}
				}
			}
		}
	}

	void ContentBrowserWindow::update(const double deltaTime)
	{
		m_dir.refreshTimer.tick(deltaTime);
		if (m_dir.refreshTimer.isExpired())
		{
			m_dir = Dir(m_dir.path);
		}
	}

	ContentBrowserWindow::Dir::Dir(const std::filesystem::path& path)
		: path(path)
		, parent(path.parent_path())
		, files()
		, refreshTimer(10.0)
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

	REFLECT_EDITOR(ContentBrowserWindow);
}