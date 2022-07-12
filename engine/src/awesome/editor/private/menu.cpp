#include "menu.h"

#include <awesome/application/application.h>
#include <awesome/editor/private/menu_layout.h>

#include <awesome/editor/menu_items/new_scene_menu_item.h>
#include <awesome/editor/menu_items/save_scene_as_menu_item.h>
#include <awesome/editor/menu_items/save_scene_menu_item.h>
#include <awesome/editor/menu_items/show_windows_menu_item.h>
#include <awesome/editor/menu_items/sprite_animation_menu_item.h>
#include <awesome/editor/menu_items/sprite_menu_item.h>

namespace editor
{
	void Menu::init()
	{
		TypeFactory::load<NewSceneMenuItem>();
		TypeFactory::load<SaveSceneMenuItem>();
		TypeFactory::load<SaveSceneAsMenuItem>();
		TypeFactory::load<ShowWindowsMenuItem>();
		TypeFactory::load<SpriteAnimationMenuItem>();
		TypeFactory::load<SpriteMenuItem>();

		static std::set<std::string> types = TypeFactory::list("MenuItem");
		for (const std::string& type : types)
		{
			MenuItem* const item = TypeFactory::instantiate<MenuItem>(type);
			if (item)
			{
				m_menuItems.push_back(MenuItemPtr(item));
			}
		}
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

		for (const auto& item : m_menuItems)
		{
			item->render();
		}
		m_saveFileDialog.render();
	}

	void Menu::menuAssets()
	{
		if (MenuLayout::beginMenu("Assets"))
		{
			for (const auto& item : m_menuItems)
			{
				if (item->getCategory() == "Assets" && MenuLayout::item(item->getName()))
				{
					item->execute();
				}
			}
			MenuLayout::endMenu();
		}
	}

	void Menu::menuFile()
	{
		if (MenuLayout::beginMenu("File"))
		{
			if (MenuLayout::item("Exit"))
			{
				Application::instance().exit();
			}

			MenuLayout::endMenu();
		}
	}

	void Menu::menuScene()
	{
		if (MenuLayout::beginMenu("Scene"))
		{
			for (const auto& item : m_menuItems)
			{
				if (item->getCategory() == "Scene" && MenuLayout::item(item->getName()))
				{
					item->execute();
				}
			}
			MenuLayout::endMenu();
		}
	}

	void Menu::menuView()
	{
		if (MenuLayout::beginMenu("View"))
		{
			for (const auto& item : m_menuItems)
			{
				if (item->getCategory() == "View" && MenuLayout::item(item->getName()))
				{
					item->execute();
				}
			}
			MenuLayout::endMenu();
		}
	}
}