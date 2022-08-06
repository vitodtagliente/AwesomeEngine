#include "graphics_serializer.h"

#include <awesome/graphics/color.h>
#include <awesome/graphics/texture_coords.h>
#include <awesome/graphics/texture_rect.h>

bool GraphicsSerializer::canSerialize(const FieldDescriptor& field)
{
	return field.typeStr == "graphics::Color"
		|| field.typeStr == "graphics::TextureCoords"
		|| field.typeStr == "graphics::TextureRect"
		;
}

json::value GraphicsSerializer::serialize(const FieldDescriptor& field)
{
	if (field.typeStr == "graphics::Color")
	{
		const graphics::Color& color = field.value<graphics::Color>();
		return json::object({
			{"r", color.red},
			{"g", color.green},
			{"b", color.blue},
			{"a", color.alpha}
			});
	}
	else if (field.typeStr == "graphics::TextureCoords")
	{
		const graphics::TextureCoords& coords = field.value<graphics::TextureCoords>();
		return json::object({
			{"u", coords.u},
			{"v", coords.v}
			});
	}
	else if (field.typeStr == "graphics::TextureRect")
	{
		const graphics::TextureRect& rect = field.value<graphics::TextureRect>();
		return json::object({
			{"x", rect.x},
			{"y", rect.y},
			{"width", rect.width},
			{"height", rect.height}
			});
	}
	return json::value();
}

bool GraphicsSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	if (!value.is_object())
		return false;

	if (field.typeStr == "graphics::Color")
	{
		graphics::Color& color = field.value<graphics::Color>();
		color.red = value.safeAt("r").as_number(0.0f).as_float();
		color.green = value.safeAt("g").as_number(0.0f).as_float();
		color.blue = value.safeAt("b").as_number(0.0f).as_float();
		color.alpha = value.safeAt("a").as_number(0.0f).as_float();
	}
	else if (field.typeStr == "graphics::TextureCoords")
	{
		graphics::TextureCoords& coords = field.value<graphics::TextureCoords>();
		coords.u = value["u"].as_number(0.0f).as_float();
		coords.v = value["v"].as_number(0.0f).as_float();
	}
	else if (field.typeStr == "graphics::TextureRect")
	{
		graphics::TextureRect& rect = field.value<graphics::TextureRect>();
		rect.x = value.safeAt("x").as_number(0.0f).as_float();
		rect.y = value.safeAt("y").as_number(0.0f).as_float();
		rect.width = value.safeAt("width").as_number(0.0f).as_float();
		rect.height = value.safeAt("height").as_number(0.0f).as_float();
	}
	return true;
}
