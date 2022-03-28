/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/graphics/texture_rect.h>

#include "image_asset.h"

struct Sprite final
{
	Sprite();
	Sprite(const ImageAssetPtr& image);
	Sprite(const ImageAssetPtr& image, const graphics::TextureRect& rect);
	Sprite(const Sprite& other);
	~Sprite();

	Sprite& operator= (const Sprite& other);
	bool operator== (const Sprite& other) const;
	bool operator!= (const Sprite& other) const;

	ImageAssetPtr image;
	graphics::TextureRect rect;
};