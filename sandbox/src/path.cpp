#include "path.h"

#include <awesome/editor/context.h>
#include <awesome/graphics/gizmos.h>
#include <awesome/graphics/renderer.h>

Path::Path()
	: steps()
	, color(graphics::Color::Red)
{
}

void Path::render(graphics::Renderer& renderer)
{
	for (size_t i = 0; i < steps.size() - 1; ++i)
	{
		renderer.getGizmos().line(steps[i], steps[i + 1], color);
	}
}

void Path::inspect(editor::Context& context)
{
	context.input("color", &color);
}