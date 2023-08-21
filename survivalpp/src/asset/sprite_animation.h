#pragma once

#include <vector>

#include "graphics/texture_rect.h"

#include "asset.h"

struct SpriteAnimationFrame
{
	graphics::TextureRect rect;
	double duration{ 1.0f };
};

struct SpriteAnimation : public Asset
{
	bool loop{ false };
	std::string texture;
	int startingFrame{ 0 };
	std::vector<SpriteAnimationFrame> frames;
};