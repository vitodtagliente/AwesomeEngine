#include "orthographic_camera.h"

#include <awesome/application/canvas.h>
#include <awesome/editor/layout.h>
#include <awesome/entity/world.h>
#include <awesome/graphics/context.h>
#include <awesome/graphics/renderer.h>
#include <awesome/math/matrix4.h>

void OrthographicCamera::update(const double deltaTime)
{
	Camera::update(deltaTime);

	Canvas& canvas = Canvas::instance();
	graphics::Renderer& renderer = graphics::Context::instance().renderer;
	renderer.setViewport(canvas.getWidth(), canvas.getHeight());
}

json::value OrthographicCamera::serialize() const
{
	json::value data = Camera::serialize();
	data["nearPlane"] = nearPlane;
	data["farPlane"] = farPlane;
	data["pixelPerfect"] = pixelPerfect;
	data["pixelsPerUnit"] = pixelsPerUnit;
	return data;
}

void OrthographicCamera::deserialize(const json::value& value)
{
	Camera::deserialize(value);
	nearPlane = value["nearPlane"].as_number(-30.f).as_float();
	farPlane = value["farPlane"].as_number(1000.f).as_float();
	pixelPerfect = value["pixelPerfect"].as_bool(true);
	pixelsPerUnit = value["pixelsPerUnit"].as_number(32).as_int();
}

void OrthographicCamera::inspect()
{
	Camera::inspect();
	editor::Layout::input("Near Plane", nearPlane);
	editor::Layout::input("Far Plane", farPlane);
	editor::Layout::input("Pixel Perfect", pixelPerfect);
	editor::Layout::input("Pixel per unit", pixelsPerUnit);
}

math::matrix4 OrthographicCamera::computeProjectionMatrix()
{
	Canvas& canvas = Canvas::instance();
	const unsigned int width = canvas.getWidth();
	const unsigned int height = canvas.getHeight();

	// pixel perfect
	const float w = pixelPerfect ? static_cast<float>(width) / 2 / pixelsPerUnit : static_cast<float>(width) / 2;
	const float h = pixelPerfect ? static_cast<float>(height) / 2 / pixelsPerUnit : static_cast<float>(height) / 2;
	return math::mat4::orthographic(-w, w, -h, h, nearPlane, farPlane);
}

REFLECT_COMPONENT(OrthographicCamera)