#include "renderable.h"

#include <glad/glad.h>

Renderable::Renderable()
	: m_id()
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
		for (VertexBuffer& vertexBuffer : vertexBuffers)
		{
			vertexBuffer.bind();
			vertexBuffer.activateLayout();
		}
		for (IndexBuffer& indexBuffer : indexBuffers)
		{
			indexBuffer.bind();
		}
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
	for (VertexBuffer& vertexBuffer : vertexBuffers)
	{
		vertexBuffer.free();
	}
	for (IndexBuffer& indexBuffer : indexBuffers)
	{
		indexBuffer.free();
	}
}

VertexBuffer* Renderable::addVertexBuffer(size_t size, BufferUsageMode usageMode)
{
	VertexBuffer& vertexBuffer = vertexBuffers.emplace_back(size, usageMode);
	return &vertexBuffer;
}

IndexBuffer* Renderable::addIndexBuffer(size_t size, BufferUsageMode usageMode)
{
	IndexBuffer& indexBuffer = indexBuffers.emplace_back(size, usageMode);
	return &indexBuffer;
}
