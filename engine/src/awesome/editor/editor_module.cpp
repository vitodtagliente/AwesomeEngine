#include "editor_module.h"

#include <assert.h>

#include <awesome/asset/asset_library.h>
#include <awesome/engine/canvas.h>

#include "editor_state.h"
#include "editor_style.h"
#include "editor_ui.h"

#include "private/editor_menu.h"

EditorMenu* menu{ nullptr };
extern EditorState* editor_state{ nullptr };

bool EditorModule::startup()
{
	EditorUI::Runtime::startup(Canvas::instance().getHandler());

	EditorUI::Style::apply(EditorStyle{});

	menu = new EditorMenu();
	menu->init();

	editor_state = new EditorState();
	editor_state->path = AssetLibrary::instance().path();
	editor_state->init();

	return true;
}

void EditorModule::shutdown()
{
	editor_state->uninit();
	delete editor_state;
	EditorUI::Runtime::shutdown();
	delete menu;
}

void EditorModule::preRendering()
{
	EditorUI::Runtime::preRendering();
}

void EditorModule::render()
{
	for (const auto& window : editor_state->getWindows())
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

void EditorModule::postRendering()
{
	EditorUI::Runtime::postRendering();
}

void EditorModule::update(const double deltaTime)
{
	EditorUI::Runtime::update();

	for (const auto& window : editor_state->getWindows())
	{
		window->update(deltaTime);
	}
}