#include "dialog_layout.h"

SaveFileDialog DialogLayout::s_saveFileDialog{};

void DialogLayout::save(const std::string& title, const std::string& extension, const std::function<void(const std::filesystem::path&)>& handler)
{
	if (s_saveFileDialog.isOpen()) return;

	s_saveFileDialog.open(title, extension, handler);
}

void DialogLayout::render()
{
	s_saveFileDialog.render();
}
