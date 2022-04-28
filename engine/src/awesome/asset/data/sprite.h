/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/graphics/texture_rect.h>

struct Sprite final
{
	Sprite();
	Sprite(const ImageAssetPtr& image);
	Sprite(const ImageAssetPtr& image, const graphics::TextureRect& rect);
	Sprite(const Sprite& other);
	~Sprite();

	static Sprite load(const std::filesystem::path& filename);
	void save(const std::filesystem::path& filename);

	Sprite& operator= (const Sprite& other);
	bool operator== (const Sprite& other) const;
	bool operator!= (const Sprite& other) const;

	ImageAssetPtr image;
	graphics::TextureRect rect;
};