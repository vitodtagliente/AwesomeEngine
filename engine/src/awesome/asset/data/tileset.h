/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/math/vector2.h>

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
	PROPERTY() ImageAssetPtr image;
	PROPERTY() std::vector<std::unique_ptr<Tile>> tiles;
	PROPERTY() math::vec2 tileSize{ 32.0f, 32.0f };

	GENERATED_BODY()
};