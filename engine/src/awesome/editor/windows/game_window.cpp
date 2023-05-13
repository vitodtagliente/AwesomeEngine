#include "game_window.h"

#include <awesome/editor/editor_ui.h>

char* const GameWindow::getTitle() const
{
	return "Game";
}

void GameWindow::render()
{
	const math::vec2 size = EditorUI::windowSize();
	// EditorUI::image
}