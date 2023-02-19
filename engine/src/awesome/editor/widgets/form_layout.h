/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/asset/image_asset.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_rect.h>

struct FormLayout final
{
	FormLayout() = delete;

	static bool button(char* const name);
	static bool button(char* const name, int width, int height);
	static bool button(char* const name, const graphics::Color& color);
	static bool button(char* const name, const graphics::Color& color, int width, int height);
	static void hint(const std::string& text);
	static void image(const ImageAssetPtr& image);
	static void image(const ImageAssetPtr& image, float width, float height);
	static void image(const ImageAssetPtr& image, const graphics::TextureRect& rect);
	static void image(const ImageAssetPtr& image, const graphics::TextureRect& rect, float width, float height);
	static bool imageButton(const ImageAssetPtr& image);
	static bool imageButton(const ImageAssetPtr& image, float width, float height);
	static bool imageButton(const ImageAssetPtr& image, const graphics::TextureRect& rect);
	static bool imageButton(const ImageAssetPtr& image, const graphics::TextureRect& rect, float width, float height);
};