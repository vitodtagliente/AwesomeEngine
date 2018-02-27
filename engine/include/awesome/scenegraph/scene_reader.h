#pragma once

#include "object.h"

namespace Awesome
{
	namespace Scenegraph
	{
		class SceneReader
		{
		private:
			Object* begin_object{ nullptr };
			Object* current_object{ nullptr };
			int child_index{ -1 };
			bool reading{ true };

		public:
			SceneReader(Object* begin_object);

			Object* const begin() { return begin_object; }
			Object* const next();
			bool end() const { return !reading; }
		};
	}
}