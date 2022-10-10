#include "settings_window.h"

#include <awesome/application/application.h>
#include <awesome/data/json_file.h>
#include <awesome/editor/layout.h>

SettingsWindow::SettingsWindow()
	: m_settings(Application::instance().getSettings())
{
}

void SettingsWindow::render()
{
	Layout::input("FPS", m_settings.fps);
	Layout::input("Mode", m_settings.mode);
	std::string path = m_settings.workspacePath.string();
	Layout::input("Workspace Path", path);
	if (path != m_settings.workspacePath.string())
	{
		m_settings.workspacePath = path;
	}

	Layout::separator();

	Layout::input("Editor Scene", m_settings.editorScene);
	Layout::input("Server Scene", m_settings.serverScene);
	Layout::input("Standalone Scene", m_settings.standaloneScene);

	Layout::separator();

	Layout::input("Server IP", m_settings.serverIp);
	Layout::input("Server Port", m_settings.serverPort);
	Layout::input("Max Server Connections", m_settings.maxServerConnections);

	Layout::separator();

	if (Layout::button(TextIcon::save(" Save")))
	{
		JsonFile::save(m_settings, std::filesystem::current_path() / "settings.json");
	}
}