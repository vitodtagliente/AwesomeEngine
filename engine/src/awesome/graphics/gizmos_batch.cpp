#include "gizmos_batch.h"

#include "context.h"

namespace graphics
{
	GizmosBatch::Batch::Batch(int size)
		: m_size(size)
		, m_data()
	{
	}

	void GizmosBatch::Batch::batch(const math::vec3& position, const Color& color)
	{
		m_data.push_back(std::make_pair(position, color));
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
		m_batches.push_back(Batch(batchSize));
	}

	void GizmosBatch::batch(const math::vec3& position, const Color& color)
	{
		findNextBatch().batch(position, color);
	}

	void GizmosBatch::clear()
	{
		m_batches.clear();
		m_batchIndex = 0;
		m_batches.push_back(Batch(m_batchSize));
	}

	std::vector<Command*> GizmosBatch::commands() const
	{
		std::vector<Command*> commands;
		for (auto it = m_batches.begin(); it != m_batches.end(); ++it)
		{
			if (it->data().empty()) continue;

			GizmosCommand* command = new GizmosCommand();
			command->data = it->data();
			commands.push_back(command);
		}
		return commands;
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

	void GizmosCommand::execute(Context& context)
	{
		context.drawLines(data);
	}
}