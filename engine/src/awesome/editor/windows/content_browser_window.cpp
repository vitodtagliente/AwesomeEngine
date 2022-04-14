#include "content_browser_window.h"

#include <awesome/application/input.h>
#include <awesome/core/string_util.h>
#include <awesome/data/archive.h>
#include <awesome/data/asset_library.h>
#include <awesome/editor/icons.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>
#include <awesome/entity/entity.h>

namespace editor
{
	ContentBrowserWindow::ContentBrowserWindow()
		: Window()
		, m_root(State::instance().path)
		, m_filter()
		, m_dir(m_root)
		, m_isRenaming()
		, m_rename()
	{

	}

	void ContentBrowserWindow::render()
	{
		State& state = State::instance();

		if (Layout::button(ICON_FA_PLUS))
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
		Layout::input(ICON_FA_SEARCH, m_filter);
		if (previousFilter != m_filter)
		{
			state.select();
		}

		Layout::separator();

		if (m_root != m_dir.path && Layout::selectable("..", false))
		{
			m_dir = Dir(m_dir.parent);
			State::instance().path = m_dir.parent;
			return;
		}

		for (const std::filesystem::path& file : m_dir.files)
		{
			const bool isSelected = state.selection.has_value()
				&& state.selection->type == State::Selection::Type::Asset
				&& state.selection->asAsset()->filename == file.string();

			if (isSelected && m_isRenaming)
			{
				Layout::rename(m_rename);
			}
			else
			{
				if (!m_filter.empty() && !StringUtil::contains(file.string(), m_filter, StringUtil::CompareMode::IgnoreCase))
				{
					continue;
				}

				if (Layout::selectable(file.stem().string(), isSelected))
				{
					m_isRenaming = false;

					// is directory
					if (!file.has_extension())
					{
						m_dir = Dir(file);
						state.path = m_dir.path;
						return;
					}
					else
					{
						Asset descriptor = Asset::load(file.string());
						std::shared_ptr<Asset> asset = AssetLibrary::instance().find(descriptor.id);
						if (asset)
						{
							state.select(asset);
						}
						else
						{
							state.select();
						}
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

		if (!hasFocus())
		{
			return;
		}

		State& state = State::instance();
		const bool hasSelectedAsset = state.selection.has_value()
			&& state.selection->type == State::Selection::Type::Asset;
		Input& input = Input::instance();

		if (m_isRenaming)
		{
			if (input.isKeyPressed(KeyCode::Enter) || input.isKeyPressed(KeyCode::Escape))
			{
				m_isRenaming = false;
				const std::string extension = state.selection->asAsset()->filename.stem().extension().string();
				std::filesystem::rename(state.selection->asAsset()->filename, state.selection->asAsset()->filename.parent_path() / (m_rename + extension + Asset::Extension));
				std::filesystem::rename(state.selection->asAsset()->filename.parent_path() / state.selection->asAsset()->filename.stem(), state.selection->asAsset()->filename.parent_path() / (m_rename + extension));
				m_rename.clear();
				m_dir.refresh();
			}
		}
		else if (hasSelectedAsset)
		{
			if (input.isKeyPressed(KeyCode::F2))
			{
				m_isRenaming = true;
				m_rename = state.selection->asAsset()->filename.stem().stem().string();
			}
			else if (input.isKeyPressed(KeyCode::Delete))
			{
				std::filesystem::remove(state.selection->asAsset()->filename);
				std::filesystem::remove(state.selection->asAsset()->filename.parent_path() / state.selection->asAsset()->filename.stem());
				m_dir.refresh();
			}
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

	void ContentBrowserWindow::Dir::refresh()
	{
		refreshTimer.expire();
	}

	REFLECT_WINDOW(ContentBrowserWindow);
}