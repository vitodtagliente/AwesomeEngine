#include "settings_window.h"

#include <awesome/editor/editor_ui.h>
#include <awesome/engine/engine.h>

char* const SettingsWindow::getTitle() const
{
	return "Settings";
}

void SettingsWindow::render()
{
	EngineSettings& settings = Engine::instance().settings;

	if (EditorUI::collapsingHeader("General"))
	{
		EditorUI::input("FPS", settings.fps);
		EditorUI::input("Mode", settings.mode);
	}
	if (EditorUI::collapsingHeader("Scene"))
	{
		EditorUI::input("Editor Starting Scene", settings.editorStartingScene);
		EditorUI::input("Server Starting Scene", settings.serverStartingScene);
		EditorUI::input("Standalone Starting Scene", settings.standaloneStartingScene);
	}

	EditorUI::separator();

	if (EditorUI::button((EditorUI::Icon::save + " Save").c_str()))
	{
		settings.save();
	}
}