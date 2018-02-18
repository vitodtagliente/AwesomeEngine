#pragma once

#include "../scenegraph/scene.h"

namespace Awesome
{
	namespace Rendering
	{
		class Renderer
		{
			friend class Scenegraph::Scene;

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