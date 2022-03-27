/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include <awesome/data/asset.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture.h>
#include <awesome/graphics/texture_coords.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>

namespace editor
{
	class Layout
	{
	private:
		Layout() = default;

	public:

		static void begin(const std::string& name);
		static bool beginCombo(const std::string& name);
		static bool button(const std::string& name);
		static bool button(const std::string& name, int width, int height);
		static bool collapsingHeader(const std::string& name);
		static void end();
		static void endCombo();
		static void image(const std::shared_ptr<ImageAsset>& image);
		static void input(const std::string& name, int* value);
		static void input(const std::string& name, bool* value);
		static void input(const std::string& name, float* value);
		static void input(const std::string& name, std::string* value, size_t size);
		static void input(const std::string& name, vec2* value);
		static void input(const std::string& name, vec3* value);
		static void input(const std::string& name, graphics::Color* value);
		static void input(const std::string& name, graphics::TextureCoords* value);
		static void input(const std::string& name, graphics::TextureRect* value);
		static void newLine();
		static void sameLine();
		static bool selectable(const std::string& name, bool selected);
		static void separator();
		static void scroll(float position);
		static void scrollToBottom();
		static void text(const std::string& str);
		static void textWrapped(const std::string& str);
	};
}