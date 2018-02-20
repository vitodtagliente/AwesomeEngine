#pragma once

#include "../../scenegraph/component.h"
#include "../shading/material.h"

namespace Awesome
{
	namespace Rendering
	{
		class RenderingComponent : public Scenegraph::Component
		{
		public:
			Material* material{ nullptr };

			virtual void render();
		};
	}
}