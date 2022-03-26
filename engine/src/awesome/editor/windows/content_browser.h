/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include <awesome/editor/window.h>

namespace editor
{
	class Context;

	class ContentBrowser : public Window
	{
	public:
		ContentBrowser();

		std::string getTitle() const override;
		void render(Context& context) override;

	private:

		struct Dir
		{
			Dir(const std::string& path);
			Dir(const std::filesystem::path& path);

			std::filesystem::path path;
			std::filesystem::path parent;
			std::vector<std::filesystem::path> files;
		};

		std::filesystem::path m_contentPath;
		Dir m_dir;
	};
}