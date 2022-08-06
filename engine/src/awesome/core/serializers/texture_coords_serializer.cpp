#include "texture_coords_serializer.h"

#include <awesome/graphics/texture_coords.h>

std::string TextureCoordsSerializer::type()
{
	return "graphics::TextureCoords";
}

json::value TextureCoordsSerializer::serialize(const FieldDescriptor& field)
{
	const graphics::TextureCoords& coords = field.value<graphics::TextureCoords>();
	return json::object({
		{"u", coords.u},
		{"v", coords.v}
		});
}

bool TextureCoordsSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	if (!value.is_object())
		return false;

	graphics::TextureCoords& coords = field.value<graphics::TextureCoords>();
	coords.u = value["u"].as_number(0.0f).as_float();
	coords.v = value["v"].as_number(0.0f).as_float();
	return true;
}
