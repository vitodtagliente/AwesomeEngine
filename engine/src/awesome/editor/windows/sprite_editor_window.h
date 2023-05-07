/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/editor/window.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/math/vector2.h>

class SpriteEditorWindow : public Window
{
public:
	virtual char* const getTitle() const override;
	virtual void render() override;

private:
	math::vec2i m_cellCount{ 1,1 };
	math::vec2i m_cellSize{ 32,32 };
	ImageAsset m_image;
	graphics::TextureRect m_rect;
};