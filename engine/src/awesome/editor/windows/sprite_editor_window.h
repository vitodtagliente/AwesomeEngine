/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/editor/window.h>
#include <awesome/graphics/texture_rect.h>

class SpriteEditorWindow : public Window
{
public:
	virtual char* const getTitle() const override;
	virtual void render() override;

private:
	int m_cols{ 1 };
	int m_columnIndex{ 0 };
	graphics::TextureRect m_rect; 
	ImageAsset m_image;
	int m_rowIndex{ 0 };
	int m_rows{ 1 };
};