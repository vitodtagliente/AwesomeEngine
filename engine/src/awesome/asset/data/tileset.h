/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>
#include <awesome/graphics/texture_rect.h>

#include "tileset_generated.h"

CLASS(Category = Data, AssetType = Tileset)
struct Tile : public Type
{
	PROPERTY() uuid id;
	PROPERTY() graphics::TextureRect rect;

	GENERATED_BODY()
};

CLASS(Category = Data)
struct Tileset : public Type
{
	PROPERTY() std::vector<std::unique_ptr<Tile>> tiles;

	GENERATED_BODY()
};