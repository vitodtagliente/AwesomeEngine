#include "sprite_batch.h"

#include "context.h"

namespace graphics
{
#define TRANSFORM_COMPONENTS 16
#define RECT_COMPONENTS 4
#define COLOR_COMPONENTS 4

	SpriteBatch::Batch::Data::Data(const size_t size)
		: transforms()
		, rects()
		, colors()
	{
		transforms.reserve(size * TRANSFORM_COMPONENTS);
		rects.reserve(size * RECT_COMPONENTS);
		colors.reserve(size * COLOR_COMPONENTS);
	}

	SpriteBatch::Batch::Batch(const size_t size)
		: count(0)
		, data(size)
		, texture()
		, size(size)
	{

	}

	void SpriteBatch::Batch::batch(const math::mat4& matrix, const TextureRect& rect, const Color& color)
	{
		data.transforms.insert(data.transforms.end(), matrix.data, matrix.data + matrix.length);
		data.rects.insert(data.rects.end(), { rect.x, rect.y, rect.width, rect.height });
		data.colors.insert(data.colors.end(), { color.red, color.green, color.blue, color.alpha });
		++count;
	}

	void SpriteBatch::Batch::clear()
	{
		count = 0;
		texture = nullptr;
		data.transforms.clear();
		data.rects.clear();
		data.colors.clear();
	}

	SpriteBatch::SpriteBatch(const size_t batchSize)
		: m_batchSize(batchSize)
		, m_batches()
	{
		// 20 texture slot by default
		for (int i = 0; i < 20; ++i)
		{
			m_batches.push_back(Batch(batchSize));
		}
	}

	void SpriteBatch::batch(Texture* const texture, const math::mat4& matrix, const TextureRect& rect, const Color& color)
	{
		Batch& batch = findNextBatch(texture);
		if (!batch.full())
		{
			batch.batch(matrix, rect, color);
		}
	}

	void SpriteBatch::flush(Context* context)
	{
		for (auto& batch : m_batches)
		{
			context->drawSprites(batch.texture, batch.data.transforms, batch.data.rects, batch.data.colors);
			batch.clear();
		}
	}

	SpriteBatch::Batch& SpriteBatch::findNextBatch(Texture* const texture)
	{
		auto it = std::find_if(m_batches.begin(), m_batches.end(), [&texture](const Batch& batch) -> bool
			{
				return batch.texture == texture;
			}
		);

		if (it != m_batches.end())
		{
			return *it;
		}

		it = std::find_if(m_batches.begin(), m_batches.end(), [](const Batch& batch) -> bool
			{
				return batch.texture == nullptr;
			}
		);

		if (it != m_batches.end())
		{
			it->texture = texture;
			return *it;
		}

		return m_batches.emplace_back(Batch(m_batchSize));
	}
}