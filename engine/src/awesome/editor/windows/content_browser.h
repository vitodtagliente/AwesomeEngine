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
	class ContentBrowser : public Window
	{
	public:
		ContentBrowser();

		std::string getTitle() const override;
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
		};

		std::filesystem::path m_contentPath;
		Dir m_dir;
		std::string m_newFolderName;
	};
}