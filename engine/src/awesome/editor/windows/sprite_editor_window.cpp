#include "sprite_editor_window.h"

#include <awesome/editor/editor_ui.h>

char* const SpriteEditorWindow::getTitle() const
{
	return "Sprite Editor";
}

void SpriteEditorWindow::render()
{
	EditorUI::input("Image", m_image);
	if (!m_image.ready()) return;

	EditorUI::input("Columns", m_cols);
	EditorUI::input("Rows", m_rows);
	EditorUI::input("Column Index", m_columnIndex);
	EditorUI::input("Row Index", m_rowIndex);
	if (EditorUI::button((EditorUI::Icon::search + " Preview size").c_str()))
	{
		m_rect.width = static_cast<float>(1.0 / m_cols);
		m_rect.height = static_cast<float>(1.0 / m_rows);
	}
	EditorUI::sameLine();
	if (EditorUI::button((EditorUI::Icon::search + " Preview index").c_str()))
	{
		m_rect.x = static_cast<float>(m_columnIndex) * static_cast<float>(1.0 / m_cols);
		m_rect.y = static_cast<float>(m_rowIndex) * static_cast<float>(1.0 / m_rows);
	}
	EditorUI::sameLine();
	if (EditorUI::button((EditorUI::Icon::eraser + " Reset").c_str()))
	{
		m_rect.width = m_rect.height = 1.f;
		m_cols = m_rows = 1;
		m_rect.x = m_rect.y = 0.f;
		m_columnIndex = m_rowIndex = 0;
	}
	EditorUI::input("Rect", m_rect);
	EditorUI::image(m_image, m_rect);
}