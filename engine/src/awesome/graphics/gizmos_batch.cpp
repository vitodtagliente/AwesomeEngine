#include "gizmos_batch.h"

#include "context.h"

namespace graphics
{
#define VERTICE_COMPONENTS 7

	GizmosBatch::Batch::Batch(int size)
		: m_size(size)
		, m_data()
	{
		m_data.reserve(size * VERTICE_COMPONENTS);
	}

	void GizmosBatch::Batch::batch(const math::vec3& position, const Color& color)
	{
		m_data.insert(m_data.end(), { position.x, position.y, position.z, color.red, color.green, color.blue, color.alpha });
	}

	void GizmosBatch::Batch::clear()
	{
		m_data.clear();
	}

	GizmosBatch::GizmosBatch(const int batchSize)
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
			if (it->data().empty()) continue;

			context->drawLines(it->data());
			it->clear();
		}
		m_batchIndex = 0;
	}

	GizmosBatch::Batch& GizmosBatch::findNextBatch()
	{
		if (m_batches[m_batchIndex].full())
		{
			m_batches.push_back(Batch(m_batchSize));
			++m_batchIndex;
		}
		return m_batches[m_batchIndex];
	}
}