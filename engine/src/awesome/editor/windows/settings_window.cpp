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

	if (EditorUI::collapsingHeader("Common"))
	{
		EditorUI::input("FPS", settings.fps);
		EditorUI::input("Mode", settings.mode);
	}
	if (EditorUI::collapsingHeader("Render"))
	{
		RendererSettings& renderer = settings.renderer;
		EditorUI::input("Render Collisions", renderer.renderCollisions);
		EditorUI::input("Collision Wire Color", renderer.collisionWireColor);
		EditorUI::input("Render QuadTree", renderer.renderQuadtree);
		EditorUI::input("QuadTree Wire Color", renderer.quadtreeWireColor);
	}
	if (EditorUI::collapsingHeader("Scene"))
	{
		SceneSettings& scene = settings.scene;
		EditorUI::input("Editor Starting Scene", scene.editor);
		EditorUI::input("Server Starting Scene", scene.server);
		EditorUI::input("Standalone Starting Scene", scene.standalone);
	}

	EditorUI::separator();

	if (EditorUI::button((EditorUI::Icon::save + " Save").c_str()))
	{
		settings.save();
	}
}