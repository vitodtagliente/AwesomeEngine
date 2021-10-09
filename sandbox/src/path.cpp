#include "path.h"

#include <awesome/graphics/gizmos.h>
#include <awesome/graphics/renderer.h>

Path::Path()
	: steps()
	, color(Color::Red)
{
}

void Path::render(Renderer& renderer)
{
	for (size_t i = 0; i < steps.size() - 1; ++i)
	{
		renderer.getGizmos().line(steps[i], steps[i + 1], color);
	}
}