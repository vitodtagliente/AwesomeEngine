#include "orthographic_camera.h"

#include <awesome/application/canvas.h>
#include <awesome/editor/context.h>
#include <awesome/graphics/context.h>
#include <awesome/graphics/renderer.h>
#include <awesome/scene/world.h>
#include <vdtmath/matrix4.h>

OrthographicCamera::OrthographicCamera()
	: Component()
	, nearPlane(-30.f)
	, farPlane(1000.f)
	, pixelPerfect(true)
	, pixelsPerUnit(32)
{

}

void OrthographicCamera::update(World& world, const double deltaTime)
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
	context.input("nearPlane", &nearPlane);
	context.input("farPlane", &farPlane);
	context.input("pixelPerfect", &pixelPerfect);
	context.input("pixelsPerUnit", &pixelsPerUnit);
}
