/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/core/reflection.h>
#include <awesome/core/uuid.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/math/vector2.h>

#include "tileset_data_generated.h"

CLASS(Type = Data)
struct TileData : public Type
{
	static constexpr int InvalidIndex = 0;

	PROPERTY() int index{ InvalidIndex };
	PROPERTY() graphics::TextureRect rect;
	PROPERTY() int value{ 0 };
	PROPERTY() bool hasCollider{ false };

	GENERATED_BODY()
};

CLASS(Type = Data, AssetType = Tileset)
struct TilesetData : public Type
{
	PROPERTY() ImageAssetPtr image;
	PROPERTY() std::vector<std::unique_ptr<TileData>> tiles;
	PROPERTY() math::vec2 size{ 1.f, 1.f };
	PROPERTY() math::vec2 tileSize{ 32.0f, 32.0f };

	GENERATED_BODY()
};