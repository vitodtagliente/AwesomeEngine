/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <awesome/core/reflection.h>
#include <awesome/core/timer.h>
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

			std::filesystem::path path;
			std::filesystem::path parent;
			std::vector<std::filesystem::path> files;
			Timer refreshTimer;

			void refresh();
		};

		std::filesystem::path m_root;
		std::string m_filter;
		Dir m_dir;
		bool m_isRenaming;
		std::string m_rename;
	};
}