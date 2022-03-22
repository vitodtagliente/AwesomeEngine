/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/core/uuid.h>
#include <awesome/encoding/json.h>
#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_coords.h>
#include <awesome/graphics/texture_rect.h>
#include <awesome/math/transform.h>
#include <awesome/math/vector2.h>
#include <awesome/math/vector3.h>
#include <awesome/math/vector4.h>

struct ISerializable
{
	virtual json::value serialize() const = 0;
	virtual void deserialize(const json::value& value) = 0;
};

template <typename T>
json::value serialize(const T& data)
{
	return T.serialize();
}

template <typename T>
bool deserialize(const json::value& value, T& data) { return true; }

template <> json::value serialize(const graphics::Color& color);
template <> json::value serialize(const graphics::TextureCoords& coords);
template <> json::value serialize(const graphics::TextureRect& rect);
template <> json::value serialize(const math::transform& t);
template <> json::value serialize(const math::vec2& v);
template <> json::value serialize(const math::vec3& v);
template <> json::value serialize(const math::vec4& v);

template <> bool deserialize(const json::value& value, graphics::Color& color);