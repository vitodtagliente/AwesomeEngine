#include <awesome/rendering/sprite_batch.h>

namespace Awesome
{
	namespace Rendering
	{
		SpriteBatch* SpriteBatch::singleton = nullptr;

		SpriteBatch::SpriteBatch() {

		}

		SpriteBatch::~SpriteBatch() {

		}

		SpriteBatch* SpriteBatch::instance() {
			if (singleton == nullptr)
				singleton = new SpriteBatch();
			return singleton;
		}

		void SpriteBatch::clear() {

		}

		void SpriteBatch::add(Texture* texture) {

		}

		void SpriteBatch::draw() {

		}
	}
}