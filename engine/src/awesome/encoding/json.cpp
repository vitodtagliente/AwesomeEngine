#include "json.h"

namespace json
{
	json::value vec2(const math::vec2& v)
	{
		return json::object({
			{"x", v.x},
			{"y", v.y}
			});
	}

	json::value vec3(const math::vec3& v)
	{
		return json::object({
			{"x", v.x},
			{"y", v.y},
			{"z", v.z}
			});
	}

	json::value transform(const math::transform& transform)
	{
		return json::object({
			{"position", vec3(transform.position)},
			{"rotation", vec3(transform.rotation)},
			{"scale", vec3(transform.scale)}
			});
	}

	json::value color(const graphics::Color& color)
	{
		return json::object({
			{"r", color.red},
			{"g", color.green},
			{"b", color.blue},
			{"a", color.alpha}
			});
	}

	json::value textureCoords(const graphics::TextureCoords& textureCoords)
	{
		return json::object({
			{"u", textureCoords.u},
			{"v", textureCoords.v}
			});
	}
}