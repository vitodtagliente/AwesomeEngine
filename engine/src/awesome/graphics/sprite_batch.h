/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <vdtmath/vector3.h>
#include <vdtmath/matrix4.h>

#include "color.h"
#include "texture.h"
#include "texture_rect.h"

namespace graphics
{
#define DEFAULT_SPRITE_BATCH_SIZE 2000

	class SpriteBatch
	{
	public:
		SpriteBatch(size_t batchSize = DEFAULT_SPRITE_BATCH_SIZE);

		void batch(Texture* const texture, const math::mat4& matrix, const TextureRect& rect, const Color& color);
		void flush(class Context* context);

	private:

		class Batch
		{
		public:

			struct Data
			{
				Data(size_t size);

				std::vector<float> transforms;
				std::vector<float> rects;
				std::vector<float> colors;
			};

			Batch(size_t size);

			inline bool empty() const { return count == 0; }
			inline bool full() const { return count >= size; }

			void batch(const math::mat4& matrix, const TextureRect& rect, const Color& color);
			void clear();

			size_t count;
			Data data;
			Texture* texture;
			size_t size;
		};

		Batch& findNextBatch(Texture* const texture);

		size_t m_batchSize;
		std::vector<Batch> m_batches;
	};
}