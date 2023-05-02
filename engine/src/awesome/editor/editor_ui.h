/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <functional>
#include <string>

#include <awesome/asset/image_asset.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_coords.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/math/transform.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/math/vector4.h>

class EditorUI final
{
public:
	struct Icon final
	{
		static const std::string copy;
		static const std::string cube;
		static const std::string eraser;
		static const std::string eye;
		static const std::string file;
		static const std::string folder;
		static const std::string horse;
		static const std::string image;
		static const std::string minus;
		static const std::string music;
		static const std::string paste;
		static const std::string pause;
		static const std::string play;
		static const std::string plus;
		static const std::string save;
		static const std::string search;
		static const std::string stop;
		static const std::string tree;
		static const std::string upload;
		static const std::string video;
	};

	static void begin(const char* const name);
	static void beginChild(const char* const name);
	static void beginChild(const char* const name, float width, float height);
	static bool beginCombo(const char* const name, const char* const value);
	static bool button(const char* const name);
	static bool button(const char* const name, int width, int height);
	static bool button(const char* const name, const graphics::Color& color);
	static bool button(const char* const name, const graphics::Color& color, int width, int height);
	static bool collapsingHeader(const char* const name);
	static void end();
	static void endChild();
	static void endCombo();
	static void hint(const std::string& text);
	static void image(const ImageAsset& image);
	static void image(const ImageAsset& image, float width, float height);
	static void image(const ImageAsset& image, const graphics::TextureRect& rect);
	static void image(const ImageAsset& image, const graphics::TextureRect& rect, float width, float height);
	static bool imageButton(const ImageAsset& image);
	static bool imageButton(const ImageAsset& image, float width, float height);
	static bool imageButton(const ImageAsset& image, const graphics::TextureRect& rect);
	static bool imageButton(const ImageAsset& image, const graphics::TextureRect& rect, float width, float height);
	static void newLine();
	static void rename(std::string& value);
	static void sameLine();
	static bool selectable(const char* const name, bool selected);
	static bool selectable(const char* const name, bool selected, const std::function<void()>& handler);
	static void separator();
	static void slider(const char* const name, int min, int max, int& value);
	static void slider(const char* const name, float min, float max, float& value);
	static void text(const char* const str);
	static void textWrapped(const char* const str);
	static void title(const char* const title);

	static void input(const char* const name, Asset& asset);
	static void input(const char* const name, int& value);
	static void input(const char* const name, bool& value);
	static void input(const char* const name, float& value);
	static void input(const char* const name, double& value);
	static void input(const char* const name, std::string& value);
	static void input(const char* const name, std::filesystem::path& value);
	static void input(const char* const name, math::transform& value);
	static void input(const char* const name, math::vec2& value);
	static void input(const char* const name, math::vec3& value);
	static void input(const char* const name, math::vec4& value);
	static void input(const char* const name, graphics::Color& value);
	static void input(const char* const name, graphics::TextureCoords& value);
	static void input(const char* const name, graphics::TextureRect& value);
	static void inputMultilineText(const char* const name, std::string& value);

private:
	static std::string id(const char* const name);
};