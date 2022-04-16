#include "content_browser_window.h"

#include <regex>

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

		m_list.onItemSelection = [this](const std::filesystem::path& file) -> void
		{
			if (file.string() == "..")
			{
				m_dir = Dir(m_dir.parent);
				State::instance().path = m_dir.parent;
			}
			else
			{
				m_selectedItem = file;
				if (std::filesystem::is_directory(file))
				{
					m_dir = Dir(file);
					State::instance().path = m_dir.path;
				}
				else
				{
					Asset descriptor = Asset::load(file);
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
		};

		static const auto getAssetFilename = [](const std::filesystem::path& filename) -> std::string
		{
			return filename.string().substr(0, filename.string().length() - std::string(Asset::Extension).length());
		};

		static const auto getAssetName = [](const std::filesystem::path& filename) -> std::string
		{
			return filename.stem().stem().string();
		};

		static const auto renameAsset = [](const std::filesystem::path& filename, const std::string& renaming) -> std::string
		{
			std::filesystem::path name = filename.stem();
			while (name.has_extension())
			{
				name = name.stem();
			}

			std::filesystem::path rename = renaming;
			while (rename.has_extension())
			{
				rename = rename.stem();
			}

			return std::regex_replace(filename.string(), std::regex(name.string()), rename.string());
		};

		m_list.onRemoveItem = [this](const std::filesystem::path& file) -> void
		{
			AssetLibrary& library = AssetLibrary::instance();
			Asset descriptor = Asset::load(file);
			std::shared_ptr<Asset> asset = library.find(descriptor.id);
			if (asset)
			{
				library.unload(asset->id);
				library.remove(asset->id);

				std::filesystem::remove(file);
				std::filesystem::remove(getAssetFilename(file));
				m_dir.refresh();
			}			
		};

		m_list.onRenameItem = [this](const std::filesystem::path& file, const std::string& name) -> void
		{
			AssetLibrary& library = AssetLibrary::instance();
			Asset descriptor = Asset::load(file);
			std::shared_ptr<Asset> asset = library.find(descriptor.id);
			if (asset)
			{
				const std::filesystem::path newAssetFilename = renameAsset(file, name);
				if (file != newAssetFilename)
				{
					std::filesystem::rename(file, newAssetFilename);
					std::filesystem::rename(getAssetFilename(file), renameAsset(getAssetFilename(file), name));
					m_dir.refresh();

					asset->filename = newAssetFilename;
					library.insert(*asset);
				}				
			}			
		};
	}

	void ContentBrowserWindow::render()
	{
		std::map<std::filesystem::path, std::string> items;
		if (m_root != m_dir.path)
		{
			items.insert(std::make_pair(m_dir.parent, ".."));
		}
		for (const auto& file : m_dir.files)
		{
			items.insert(std::make_pair(file, file.stem().string()));
		}
		m_list.render(items, !m_selectedItem.empty() ? std::optional<std::filesystem::path>(m_selectedItem) : std::nullopt);
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