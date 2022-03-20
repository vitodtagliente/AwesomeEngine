#include "orthographic_camera.h"

#include <awesome/application/canvas.h>
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
	Canvas* const canvas = Canvas::instance();
	graphics::Context* const context = graphics::Context::instance();
	if (canvas && context)
	{
		const unsigned int width = canvas->getWidth();
		const unsigned int height = canvas->getHeight();

		context->viewport(width, height);

		// pixel perfect
		const float w = pixelPerfect ? static_cast<float>(width) / 2 / pixelsPerUnit : static_cast<float>(width) / 2;
		const float h = pixelPerfect ? static_cast<float>(height) / 2 / pixelsPerUnit : static_cast<float>(height) / 2;
		context->camera = math::mat4::orthographic(-w, w, -h, h, nearPlane, farPlane);
	}
}

void OrthographicCamera::inspect(editor::Context& context)
{
	Component::inspect(context);
	context.input("Near Plane", &nearPlane);
	context.input("Far Plane", &farPlane);
	context.input("Pixel Perfect", &pixelPerfect);
	context.input("Pixel per unit", &pixelsPerUnit);
}

REFLECT_IMP(OrthographicCamera)