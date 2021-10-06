#include "renderable.h"

#include <glad/glad.h>

Renderable::Renderable(size_t vertices, size_t indices, BufferUsageMode usageMode)
	: m_id()
	, m_vertexBuffer(vertices, usageMode)
	, m_indexBuffer(indices, usageMode)
	, m_firstBinding(true)
{
	glGenVertexArrays(1, &m_id);
}

Renderable::~Renderable()
{
	free();
}

void Renderable::bind(bool forceBuffersBinding)
{
	glBindVertexArray(m_id);
	if (m_firstBinding || forceBuffersBinding)
	{
		m_vertexBuffer.bind();
		m_vertexBuffer.activateLayout();
		m_indexBuffer.bind();
		m_firstBinding = false;
	}
}

void Renderable::unbind()
{
	glBindVertexArray(0);
}

void Renderable::free()
{
	glDeleteVertexArrays(1, &m_id);
	m_vertexBuffer.free();
	m_indexBuffer.free();
}
