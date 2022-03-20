/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include "../file.h"
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