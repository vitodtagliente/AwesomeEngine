#include "content_browser_window.h"

#include <awesome/core/string_util.h>
#include <awesome/data/archive.h>
#include <awesome/data/asset_library.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>
#include <awesome/entity/entity.h>

namespace editor
{
	ContentBrowserWindow::ContentBrowserWindow()
		: Window()
		, m_contentPath(State::instance().path)
		, m_filter()
		, m_dir(m_contentPath)
	{

	}

	void ContentBrowserWindow::render()
	{
		State& state = State::instance();

		if (Layout::button("+"))
		{
			static const std::string DefaultName{ "New Folder" };
			int i = 0;
			while (true)
			{
				std::filesystem::path path = m_dir.path / (DefaultName + ((i == 0) ? "" : std::string(" ") + std::to_string(i)));
				if (!std::filesystem::exists(path))
				{
					std::filesystem::create_directory(path);
					break;
				}
				else
				{
					++i;
				}
			}
		}

		Layout::sameLine();
		const std::string previousFilter = m_filter;
		Layout::input("Filter", m_filter);
		if (previousFilter != m_filter)
		{
			state.select();
		}

		Layout::separator();

		if (m_contentPath != m_dir.path && Layout::selectable("..", false))
		{
			m_dir = Dir(m_dir.parent);
			State::instance().path = m_dir.parent;
			return;
		}

		for (const std::filesystem::path& file : m_dir.files)
		{
			if (!StringUtil::contains(file.string(), m_filter, StringUtil::CompareMode::IgnoreCase))
			{
				continue;
			}

			if (Layout::selectable(file.stem().string(),
				state.selection.has_value()
				&& state.selection->type == State::Selection::Type::Asset
				&& state.selection->asAsset()->filename == file.string()))
			{
				// is directory
				if (!file.has_extension())
				{
					m_dir = Dir(file);
					State::instance().path = m_dir.path;
					return;
				}
				else
				{
					Asset descriptor = Asset::load(file.string());
					std::shared_ptr<Asset> asset = AssetLibrary::instance().find(descriptor.id);
					if (asset)
					{
						State::instance().select(asset);
					}
					else
					{
						State::instance().select();
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

	REFLECT_WINDOW(ContentBrowserWindow);
}