#pragma once

namespace Awesome
{
	namespace Rendering
	{
		class Scenegraph::Component;

		class RenderingComponent : public Component
		{
			virtual void render();
		};
	}
}