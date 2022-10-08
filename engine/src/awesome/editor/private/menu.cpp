#include "menu.h"

#include <awesome/application/application.h>
#include <awesome/editor/private/menu_layout.h>

#include <awesome/editor/menu_items/menu_items.h>

void Menu::init()
{
	static std::vector<std::string> types = TypeFactory::list("Category", "MenuItem");
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