#include "gizmos_batch.h"

#include "context.h"

namespace graphics
{
#define VERTICE_COMPONENTS 7

	GizmosBatch::Batch::Batch(size_t size)
		: count(0)
		, data()
		, size(size)
	{
		data.reserve(size * VERTICE_COMPONENTS);
	}

	void GizmosBatch::Batch::batch(const math::vec3& position, const Color& color)
	{
		data.insert(data.end(), { position.x, position.y, position.z, color.red, color.green, color.blue, color.alpha });
		++count;
	}

	void GizmosBatch::Batch::clear()
	{
		count = 0;
		data.clear();
	}

	GizmosBatch::GizmosBatch(const size_t batchSize)
		: m_batchSize(batchSize)
		, m_batchIndex()
		, m_batches()
	{
		for (int i = 0; i < 10; ++i)
		{
			m_batches.push_back(Batch(batchSize));
		}
	}

	void GizmosBatch::batch(const math::vec3& position, const Color& color)
	{
		findNextBatch().batch(position, color);
	}

	void GizmosBatch::flush(Context* const context)
	{
		for (auto it = m_batches.begin(); it != m_batches.end(); ++it)
		{
			if (it->empty()) continue;

			context->drawLines(it->data);
			it->clear();
		}
		m_batchIndex = 0;
	}

	GizmosBatch::Batch& GizmosBatch::findNextBatch()
	{
		if (!m_batches[m_batchIndex].full())
		{
			return m_batches[m_batchIndex];
		}

		++m_batchIndex;
		if (m_batchIndex >= m_batches.size())
		{
			m_batches.push_back(Batch(m_batchSize));
		}
		return m_batches[m_batchIndex];
	}
}