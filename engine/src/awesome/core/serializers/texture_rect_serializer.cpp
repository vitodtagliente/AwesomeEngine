#include "texture_rect_serializer.h"

#include <awesome/graphics/texture_rect.h>

std::string TextureRectSerializer::type()
{
	return "graphics::TextureRect";
}

json::value TextureRectSerializer::serialize(const FieldDescriptor& field)
{
	const graphics::TextureRect& rect = field.value<graphics::TextureRect>();
	return json::object({
		{"x", rect.x},
		{"y", rect.y},
		{"width", rect.width},
		{"height", rect.height}
		});
}

bool TextureRectSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	if (!value.is_object())
		return false;

	graphics::TextureRect& rect = field.value<graphics::TextureRect>();
	rect.x = value.safeAt("x").as_number(0.0f).as_float();
	rect.y = value.safeAt("y").as_number(0.0f).as_float();
	rect.width = value.safeAt("width").as_number(0.0f).as_float();
	rect.height = value.safeAt("height").as_number(0.0f).as_float();
	return true;
}
