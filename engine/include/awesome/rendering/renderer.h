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
			friend class Scene;

		private:
			static Renderer* singleton;

		protected:
			Renderer();
			~Renderer();
			
		public:
			static Renderer* instance();

			Scene* scene{ nullptr };

			void init();
			void update(float delta_time);
			void render();
		};
	}
}