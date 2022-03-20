/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include "../window.h"

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

		struct File
		{
			File(const std::string& name, bool isDirectory);

			std::string name;
			bool isDirectory;
		};

		struct Dir
		{
			Dir(const std::string& directory);

			std::string path;
			std::string parent;
			std::vector<File> files;
		};

		Dir m_dir;
	};
}