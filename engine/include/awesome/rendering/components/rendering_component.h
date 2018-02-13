#pragma once

#include "../../scenegraph/component.h"

namespace Awesome
{
	namespace Rendering
	{
		class RenderingComponent : public Scenegraph::Component
		{
		public:
			virtual void render() = 0;
		};
	}
}