#pragma once 

#include "../scenegraph/scene.h"
#include "components/rendering_component.h"

using namespace Awesome::Scenegraph;

namespace Awesome
{
	namespace Rendering
	{
		class RenderPipeline
		{
		private:
			Scene* scene{ nullptr };
			std::vector<RenderingComponent*> render_queue{};
		
		public:
			RenderPipeline();
			RenderPipeline(Scene* new_scene);
			~RenderPipeline();

			void init();
			void update(float delta_time);
			void render();

			/* init data to render the new scene */
			void renderScene(Scene* new_scene);
		};
	}
}