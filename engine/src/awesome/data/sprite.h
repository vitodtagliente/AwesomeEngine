/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include <awesome/graphics/texture_rect.h>

#include "asset.h"

struct Sprite final
{
	Sprite();
	Sprite(const std::shared_ptr<ImageAsset>& image);
	Sprite(const std::shared_ptr<ImageAsset>& image, const graphics::TextureRect& rect);
	Sprite(const Sprite& other);
	~Sprite();

	Sprite& operator= (const Sprite& other);
	bool operator== (const Sprite& other) const;
	bool operator!= (const Sprite& other) const;

	std::shared_ptr<ImageAsset> image;
	graphics::TextureRect rect;
};