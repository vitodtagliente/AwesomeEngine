#pragma once

#include "render_queue.h"
#include "update_queue.h"
#include "../scenegraph/scenegraph.h"

namespace Awesome
{
	using namespace Scenegraph;

	namespace Rendering
	{
		class Renderer
		{
		protected:
			UpdateQueue updateQueue;
			RenderQueue renderQueue;

			Scene scene;

		public:

			virtual void init();
			virtual void update(float delta_time);
			virtual void render();
		};
	}
}