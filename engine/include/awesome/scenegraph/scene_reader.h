#pragma once

#include "scene.h"

namespace Awesome
{
	namespace Scenegraph
	{
		class SceneReader
		{
		private:
			Object* current_object{ nullptr };
			int child_index{ -1 };

		public:
			SceneReader(Scene* selected_scene);

			Object* const next();
		};
	}
}