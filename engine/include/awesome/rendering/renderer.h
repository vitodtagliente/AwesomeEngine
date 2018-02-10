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

		protected:
			Scenegraph::Scene* scene{ nullptr };

		public:
			static Renderer* instance();

			void loadScene(Scenegraph::Scene* new_scene);

			void init();
			void update(float delta_time);
			void render();
		};
	}
}