#include "editor_menu.h"

#include <awesome/editor/editor_state.h>
#include <awesome/editor/editor_ui.h>
#include <awesome/editor/widgets/dialog_layout.h>
#include <awesome/engine/engine.h>
#include <awesome/scene/scene_graph.h>

EditorMenu::EditorMenu()
	: m_editorState(EditorState::instance())
{

}

void EditorMenu::init()
{

}

void EditorMenu::render()
{
	if (EditorUI::Menu::beginBar())
	{
		menuFile();
		menuScene();
		menuAssets();
		menuView();

		EditorUI::Menu::endBar();
	}
}

void EditorMenu::menuAssets()
{
}

void EditorMenu::menuFile()
{
	if (EditorUI::Menu::begin("File"))
	{
		if (EditorUI::Menu::item("Exit"))
		{
			Engine::instance().exit();
		}

		EditorUI::Menu::end();
	}
}

void EditorMenu::menuScene()
{
	if (EditorUI::Menu::begin("Scene"))
	{
		if (EditorUI::Menu::item("New Scene..."))
		{
			m_editorState->unselectEntity();
			SceneGraph::instance().clear();
		}

		EditorUI::separator();
		bool save_as = false;
		if (EditorUI::Menu::item("Save Scene"))
		{
			SceneGraph& sceneGraph = SceneGraph::instance();
			if (sceneGraph.scene())
			{
				sceneGraph.save(sceneGraph.scene().path);
			}
			else
			{
				save_as = true;
			}
		}
		if (EditorUI::Menu::item("Save Scene as..."))
		{
			save_as = true;
		}

		if (save_as)
		{
			DialogLayout::save("Save Scene as...", ".scene", [](const std::filesystem::path& path) -> void
				{
					SceneGraph::instance().save(path);
				}
			);
		}

		EditorUI::Menu::end();
	}
}

void EditorMenu::menuView()
{
	if (EditorUI::Menu::begin("View"))
	{
		for (const auto& window : m_editorState->getWindows())
		{
			EditorUI::Menu::item(window->getTitle(), window->visible);
		}
		EditorUI::Menu::end();
	}
}