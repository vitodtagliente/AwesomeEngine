#include "color_serializer.h"

#include <awesome/graphics/color.h>

std::string ColorSerializer::type()
{
	return "graphics::Color";
}

json::value ColorSerializer::serialize(const FieldDescriptor& field)
{
	const graphics::Color& color = field.value<graphics::Color>();
	return json::object({
		{"r", color.red},
		{"g", color.green},
		{"b", color.blue},
		{"a", color.alpha}
		});
}

bool ColorSerializer::deserialize(FieldDescriptor& field, const json::value& value)
{
	graphics::Color& color = field.value<graphics::Color>();
	color.red = value.safeAt("r").as_number(0.0f).as_float();
	color.green = value.safeAt("g").as_number(0.0f).as_float();
	color.blue = value.safeAt("b").as_number(0.0f).as_float();
	color.alpha = value.safeAt("a").as_number(0.0f).as_float();
	return true;
}
