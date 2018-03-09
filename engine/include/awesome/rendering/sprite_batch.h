#pragma once

#include <vector>
#include "shading/texture.h"

namespace Awesome
{
	namespace Rendering
	{
		class SpriteBatch
		{
		private:
			static SpriteBatch* singleton;

			SpriteBatch();
			~SpriteBatch();

		public:
			static SpriteBatch* instance();

			void add(Texture* texture);
			void clear();
			void draw();
		};
	}
}