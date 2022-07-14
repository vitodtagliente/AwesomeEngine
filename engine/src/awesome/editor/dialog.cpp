#include "dialog.h"

namespace editor
{
	void Dialog::open(const std::string& title, const std::vector<std::string>& extensions, const std::function<void(const std::filesystem::path&)>& handler)
	{
		if (m_openFileDialog.isOpen() || m_saveFileDialog.isOpen()) return;

		m_openFileDialog.open(title, extensions, handler);
	}

	void Dialog::save(const std::string& title, const std::string& extension, const std::function<void(const std::filesystem::path&)>& handler)
	{
		if (m_openFileDialog.isOpen() || m_saveFileDialog.isOpen()) return;

		m_saveFileDialog.open(title, extension, handler);
	}

	void Dialog::render()
	{
		m_openFileDialog.render();
		m_saveFileDialog.render();
	}
}