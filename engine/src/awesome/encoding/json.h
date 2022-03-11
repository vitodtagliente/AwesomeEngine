/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtjson/json.h>

#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_coords.h>
#include <awesome/math/math.h>

namespace json
{
	json::value color(const graphics::Color& color);
	json::value textureCoords(const graphics::TextureCoords& textureCoords);
	json::value transform(const math::transform& transform);
	json::value vec2(const math::vec2& v);
	json::value vec3(const math::vec3& v);
}