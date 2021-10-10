/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vdtmath/vector2.h>
#include <vdtmath/vector3.h>

#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_coords.h>
#include <awesome/graphics/texture_rect.h>

namespace editor
{
	class Context
	{
	public:
		Context();

		bool collapsingHeader(const std::string& name);
		void input(const std::string& name, int* value);
		void input(const std::string& name, bool* value);
		void input(const std::string& name, float* value);
		void input(const std::string& name, std::string* value, size_t size);
		void input(const std::string& name, math::vec2* value);
		void input(const std::string& name, math::vec3* value);
		void input(const std::string& name, graphics::Color* value);
		void input(const std::string& name, graphics::TextureCoords* value);
		void input(const std::string& name, graphics::TextureRect* value);
		bool selectable(const std::string& name, bool selected);
		void text(const std::string& str);
	};
}