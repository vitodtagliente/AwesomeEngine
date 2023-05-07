#include "sprite_editor_window.h"

#include <map>
#include <sstream>
#include <string>

#include <awesome/editor/editor_ui.h>

enum class SpriteEditorMode
{
	Multiple = 0,
	Single,
};
SpriteEditorMode mode{ SpriteEditorMode::Multiple };
static const std::map<std::string, SpriteEditorMode> modeLabelMap{
	{"Multiple", SpriteEditorMode::Multiple},
	{"Single", SpriteEditorMode::Single}
};

enum class SpriteEditorSplitType
{
	CellCount = 0,
	CellSize
};
SpriteEditorSplitType splitType{ SpriteEditorSplitType::CellCount };
static const std::map<std::string, SpriteEditorSplitType> splitTypeLabelMap{
	{"Grid By Cell Count", SpriteEditorSplitType::CellCount},
	{"Grid By Cell Size", SpriteEditorSplitType::CellSize}
};

char* const SpriteEditorWindow::getTitle() const
{
	return "Sprite Editor";
}

void SpriteEditorWindow::render()
{
	EditorUI::input("Image", m_image);
	if (!m_image.ready()) return;

	EditorUI::input("Mode", mode, modeLabelMap);
	if (mode == SpriteEditorMode::Single)
	{
		EditorUI::input("Rect", m_rect);
		EditorUI::image(m_image, m_rect);
	}
	else
	{
		int spritesPerRow = 0;
		std::vector<graphics::TextureRect> sprites;

		EditorUI::input("Type", splitType, splitTypeLabelMap);
		if (splitType == SpriteEditorSplitType::CellSize)
		{
			EditorUI::input("Sprite Size", m_cellSize);

			const float sprite_width = static_cast<float>(m_cellSize.x) / m_image.resource->width;
			const float sprite_height = static_cast<float>(m_cellSize.y) / m_image.resource->height;
			spritesPerRow = static_cast<int>(1.f / sprite_width);
			const int spritesPerColumn = static_cast<int>(1.f / sprite_height);
			for (int j = 0; j < spritesPerColumn; ++j)
			{
				for (int i = 0; i < spritesPerRow; ++i)
				{
					sprites.push_back(graphics::TextureRect(static_cast<float>(i) * sprite_width, static_cast<float>(j) * sprite_height, sprite_width, sprite_height));
				}
			}
		}
		else
		{
			EditorUI::input("Columns & Rows", m_cellCount);

			spritesPerRow = m_cellCount.x;
			const float sprite_width = 1.0f / static_cast<float>(m_cellCount.x);
			const float sprite_height = 1.0f / static_cast<float>(m_cellCount.y);
			for (int j = 0; j < m_cellCount.y; ++j)
			{
				for (int i = 0; i < m_cellCount.x; ++i)
				{
					sprites.push_back(graphics::TextureRect(static_cast<float>(i) * sprite_width, static_cast<float>(j) * sprite_height, sprite_width, sprite_height));
				}
			}
		}

		float size = EditorUI::windowSize().x;
		if (spritesPerRow > 1)
		{
			size = 45.f;
		}

		for (int i = 0; i < sprites.size(); ++i)
		{
			const auto& sprite = sprites[i];

			if (i % spritesPerRow != 0)
			{
				EditorUI::sameLine();
			}
			EditorUI::Id::push(std::to_string(i).c_str());
			EditorUI::imageButton(m_image, sprites[i], size, size);

			std::ostringstream s;
			s << std::fixed << std::setprecision(4) << "(" << sprite.x << "," << sprite.y << "," << sprite.width << "," << sprite.height << ")";
			EditorUI::DragDrop::begin("graphics::TextureRect", s.str().c_str(), (void*)(&sprite), sizeof(graphics::TextureRect));
			EditorUI::Id::pop();
		}
	}
}