#pragma once 

#include "../scene/scene.h"
#include "components/rendering_component.h"

namespace Awesome
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