#include "editor.h"

#include <assert.h>

#include <awesome/asset/asset_library.h>
#include <awesome/engine/canvas.h>

#include "color_scheme.h"
#include "editor_ui.h"
#include "private/menu.h"
#include "widgets/dialog_layout.h"

Editor* Editor::s_instance{ nullptr };

Menu menu;

Editor::Editor()
	: EngineModule()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

bool Editor::startup()
{
	EditorUI::Runtime::startup(Canvas::instance().getHandler());

	ColorScheme scheme;
	scheme.apply();
	menu.init();

	state.path = AssetLibrary::instance().path();
	state.init();

	return true;
}

void Editor::shutdown()
{
	EditorUI::Runtime::shutdown();
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
	menu.render();
	DialogLayout::render();
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