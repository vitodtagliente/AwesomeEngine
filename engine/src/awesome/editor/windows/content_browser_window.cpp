#include "content_browser_window.h"

#include <awesome/core/string_util.h>
#include <awesome/data/asset_library.h>
#include <awesome/editor/layout.h>
#include <awesome/editor/state.h>

namespace editor
{
	ContentBrowserWindow::ContentBrowserWindow()
		: Window()
		, m_dir(AssetLibrary::instance().getDirectory())
		, m_list()
		, m_root(AssetLibrary::instance().getDirectory())
		, m_selectedItem()
	{
		m_list.onAddItem = [this]() -> void
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
				++i;
			}
		};

		m_list.onItemSelection = [this](const std::string& item) -> void
		{
			if (item.empty())
			{

			}
			else if (item == "..")
			{
				m_dir = Dir(m_dir.parent);
				State::instance().path = m_dir.parent;
			}
			else
			{
				m_selectedItem = item;
				std::filesystem::path path = m_dir.path / (item + Asset::Extension);
				if (std::filesystem::exists(path))
				{
					Asset descriptor = Asset::load(path.string());
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
				else // is directory
				{
					m_dir = Dir(m_dir.path / item);
					State::instance().path = m_dir.path;
					return;
				}
			}
		};

		m_list.onRemoveItem = [this](const std::string& item) -> void
		{
			std::filesystem::remove(m_dir.path / item);
			std::filesystem::remove(m_dir.path / (item + Asset::Extension));
			m_dir.refresh();
		};

		m_list.onRenameItem = [this](const std::string& item, const std::string& name) -> void
		{
			const auto& it = item.find_last_of(".");
			const std::string extension = item.substr(it);
			const std::string n_name = StringUtil::endsWith(name, extension) ? name : name + extension;
			std::filesystem::rename(m_dir.path / item, m_dir.path / n_name);
			std::filesystem::rename(m_dir.path / (item + Asset::Extension), m_dir.path / (n_name + Asset::Extension));
			m_dir.refresh();
		};
	}

	void ContentBrowserWindow::render()
	{
		std::vector<std::string> items;
		if (m_root != m_dir.path)
		{
			items.push_back("..");
		}
		std::transform(m_dir.files.begin(), m_dir.files.end(), std::back_inserter(items), [](const std::filesystem::path& file) -> std::string
			{
				return file.stem().string();
			}
		);
		m_list.render(items, m_selectedItem);
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
		: files()
		, parent(path.parent_path())
		, path(path)
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