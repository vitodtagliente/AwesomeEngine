#pragma once

#include "../scenegraph/scene.h"

namespace Awesome
{
	namespace Rendering
	{
		class Renderer
		{
		private:
			static Renderer* singleton;

			Renderer();
			
		public:
			static Renderer* instance();

			Scenegraph::Scene* scene{ nullptr };

			void init();
			void update(float delta_time);
			void render();
		};
	}
}