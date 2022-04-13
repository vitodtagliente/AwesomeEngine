#include "orthographic_camera.h"

#include <awesome/application/canvas.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/context.h>
#include <awesome/graphics/renderer.h>
#include <awesome/math/matrix4.h>

OrthographicCamera::OrthographicCamera()
	: Component()
	, nearPlane(-30.f)
	, farPlane(1000.f)
	, pixelPerfect(true)
	, pixelsPerUnit(32)
{

}

void OrthographicCamera::update(const double)
{
	Canvas& canvas = Canvas::instance();
	graphics::Context* const context = &graphics::Context::instance();
	if (context)
	{
		const unsigned int width = canvas.getWidth();
		const unsigned int height = canvas.getHeight();

		context->viewport(width, height);

		// pixel perfect
		const float w = pixelPerfect ? static_cast<float>(width) / 2 / pixelsPerUnit : static_cast<float>(width) / 2;
		const float h = pixelPerfect ? static_cast<float>(height) / 2 / pixelsPerUnit : static_cast<float>(height) / 2;
		context->camera = math::mat4::orthographic(-w, w, -h, h, nearPlane, farPlane);
	}
}

json::value OrthographicCamera::serialize() const
{
	json::value data = Component::serialize();
	data["nearPlane"] = nearPlane;
	data["farPlane"] = farPlane;
	data["pixelPerfect"] = pixelPerfect;
	data["pixelsPerUnit"] = pixelsPerUnit;
	return data;
}

void OrthographicCamera::deserialize(const json::value& value)
{
	Component::deserialize(value);
	nearPlane = value["nearPlane"].as_number(-30.f).as_float();
	farPlane = value["farPlane"].as_number(1000.f).as_float();
	pixelPerfect = value["pixelPerfect"].as_bool(true);
	pixelsPerUnit = value["pixelsPerUnit"].as_number(32).as_int();
}

void OrthographicCamera::inspect()
{
	Component::inspect();
	editor::Layout::input("Near Plane", nearPlane);
	editor::Layout::input("Far Plane", farPlane);
	editor::Layout::input("Pixel Perfect", pixelPerfect);
	editor::Layout::input("Pixel per unit", pixelsPerUnit);
}

REFLECT_COMPONENT(OrthographicCamera)