#include "menu.h"

#include <awesome/editor/editor_state.h>
#include <awesome/editor/widgets/dialog_layout.h>
#include <awesome/editor/widgets/menu_layout.h>
#include <awesome/engine/engine.h>
#include <awesome/scene/scene_graph.h>

Menu::Menu()
	: m_editorState(EditorState::instance())
{

}

void Menu::init()
{

}

void Menu::render()
{
	if (MenuLayout::beginMainMenu())
	{
		menuFile();
		menuScene();
		menuAssets();
		menuView();

		MenuLayout::endMainMenu();
	}
}

void Menu::menuAssets()
{
}

void Menu::menuFile()
{
	if (MenuLayout::beginMenu("File"))
	{
		if (MenuLayout::item("Exit"))
		{
			Engine::instance().exit();
		}

		MenuLayout::endMenu();
	}
}

void Menu::menuScene()
{
	if (MenuLayout::beginMenu("Scene"))
	{
		if (MenuLayout::item("New Scene..."))
		{
			m_editorState->unselectEntity();
			SceneGraph::instance().clear();
		}

		MenuLayout::separator();
		bool save_as = false;
		if (MenuLayout::item("Save Scene"))
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
		if (MenuLayout::item("Save Scene as..."))
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

		MenuLayout::endMenu();
	}
}

void Menu::menuView()
{
	
}