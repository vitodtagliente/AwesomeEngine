#include "gizmos_batch.h"

#include "context.h"

Batch::Batch(int size)
	: m_size(size)
	, m_data()
{
}

void Batch::batch(const math::vec3& position, const Color& color)
{
	m_data.push_back(std::make_pair(position, color));
}

void Batch::clear()
{
	m_data.clear();
}

GizmosBatch::GizmosBatch(int batchSize)
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

std::vector<Command*> GizmosBatch::generateCommands() const
{
	std::vector<Command*> commands;
	for (auto it = m_batches.begin(); it != m_batches.end(); ++it)
	{
		GizmosCommand* command = new GizmosCommand();
		command->data = it->data();
		commands.push_back(command);
	}
	return commands;
}

Batch& GizmosBatch::findNextBatch()
{
	if (m_batches[m_batchIndex].full())
	{
		m_batches.push_back(Batch(m_batchSize));
		++m_batchIndex;
	}
	return m_batches[m_batchIndex];
}

void GizmosCommand::execute(Context& contex)
{
	contex.drawLines(data);
}
