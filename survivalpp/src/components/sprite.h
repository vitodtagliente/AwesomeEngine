/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

#include "ecs/component.h"

#include "graphics/color.h"
#include "graphics/texture.h"
#include "graphics/texture_rect.h"

struct Sprite : public Component
{
	graphics::Color color{ graphics::Color::White };
	bool flipX{ false };
	bool flipY{ false };
	graphics::TextureRect rect;
	std::filesystem::path texture;
};