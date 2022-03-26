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
	class Context
	{
	public:
		Context();

		bool button(const std::string& name);
		bool button(const std::string& name, int width, int height);
		bool collapsingHeader(const std::string& name);
		void image(const std::shared_ptr<ImageAsset>& image);
		void input(const std::string& name, int* value);
		void input(const std::string& name, bool* value);
		void input(const std::string& name, float* value);
		void input(const std::string& name, std::string* value, size_t size);
		void input(const std::string& name, vec2* value);
		void input(const std::string& name, vec3* value);
		void input(const std::string& name, graphics::Color* value);
		void input(const std::string& name, graphics::TextureCoords* value);
		void input(const std::string& name, graphics::TextureRect* value);
		void newLine();
		void sameLine();
		bool selectable(const std::string& name, bool selected);
		void text(const std::string& str);
		void textWrapped(const std::string& str);
	};
}