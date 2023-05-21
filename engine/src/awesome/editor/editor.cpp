#include "editor.h"

#include <assert.h>

#include <awesome/asset/asset_library.h>
#include <awesome/engine/canvas.h>

#include "editor_style.h"
#include "editor_ui.h"

#include "private/editor_menu.h"

Editor* Editor::s_instance{ nullptr };
EditorMenu* menu{ nullptr };

Editor::Editor()
	: EngineModule()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

bool Editor::startup()
{
	EditorUI::Runtime::startup(Canvas::instance().getHandler());

	EditorUI::Style::apply(EditorStyle{});

	menu = new EditorMenu();
	menu->init();

	state.path = AssetLibrary::instance().path();
	state.init();

	return true;
}

void Editor::shutdown()
{
	state.uninit();
	EditorUI::Runtime::shutdown();
	delete menu;
}

void Editor::preRendering()
{
	EditorUI::Runtime::preRendering();
}

void Editor::render()
{
	for (const auto& window : state.getWindows())
	{
		if (!window->visible) continue;

		EditorUI::Window::begin(window->getTitle());
		window->setFocus(EditorUI::Window::isFocused());
		window->setIsHovered(EditorUI::Window::isHovered());
		window->render();
		EditorUI::Window::end();
	}
	menu->render();
}

void Editor::postRendering()
{
	EditorUI::Runtime::postRendering();
}

void Editor::update(const double deltaTime)
{
	EditorUI::Runtime::update();

	for (const auto& window : state.getWindows())
	{
		window->update(deltaTime);
	}
}