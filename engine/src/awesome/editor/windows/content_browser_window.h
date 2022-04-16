/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/core/timer.h>
#include <awesome/editor/widgets/select_list.h>
#include <awesome/editor/window.h>

namespace editor
{
	class ContentBrowserWindow : public Window
	{
	public:
		ContentBrowserWindow();

		std::string getTitle() const override { return "Content Browser"; }
		virtual void render() override;
		virtual void update(double deltaTime) override;

		REFLECT()

	private:

		struct Dir
		{
			Dir(const std::filesystem::path& path);

			std::vector<std::filesystem::path> files;
			std::filesystem::path parent;
			std::filesystem::path path;
			Timer refreshTimer;

			void refresh();
		};

		Dir m_dir;
		SelectList<std::filesystem::path> m_list;
		std::filesystem::path m_root;
		std::filesystem::path m_selectedItem;
	};
}