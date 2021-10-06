/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "index_buffer.h"
#include "vertex_buffer.h"

class Renderable
{
public:

	Renderable(size_t vertices, size_t indices, BufferUsageMode usageMode);
	~Renderable();

	void bind(bool forceBuffersBinding = false);
	void unbind();
	void free();

	inline VertexBuffer& getVertexBuffer() { return m_vertexBuffer; }
	inline IndexBuffer& getIndexBuffer() { return m_indexBuffer; }

private:

	// vertex array object
	unsigned int m_id;
	VertexBuffer m_vertexBuffer;
	IndexBuffer m_indexBuffer;
	bool m_firstBinding;
};