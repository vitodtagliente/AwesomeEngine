#pragma once

#include <string>
#include "../scenegraph/scene.h"

using namespace Awesome::Scenegraph;

namespace Awesome
{
	namespace Rendering
	{
		class Renderer
		{
		private:
			static Renderer* singleton;

		protected:
			Renderer();
			~Renderer();

			Scene* scene{ nullptr };

		public:
			static Renderer* instance();
			
			void init();
			void update(float delta_time);
			void render();

			void handleScene(Scene* current_scene);
		};
	}
}