/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include "index_buffer.h"
#include "vertex_buffer.h"

class Renderable
{
public:

	Renderable();
	~Renderable();

	void bind(bool forceBuffersBinding = false);
	void unbind();
	void free();

	inline VertexBuffer* getMainVertexBuffer() { return vertexBuffers.empty() ? nullptr : &vertexBuffers.at(0); }
	VertexBuffer* addVertexBuffer(size_t size, BufferUsageMode usageMode);
	inline IndexBuffer* getMainIndexBuffer() { return indexBuffers.empty() ? nullptr : &indexBuffers.at(0); }
	IndexBuffer* addIndexBuffer(size_t size, BufferUsageMode usageMode);

	std::vector<VertexBuffer> vertexBuffers;
	std::vector<IndexBuffer> indexBuffers;

private:

	// vertex array object
	unsigned int m_id;
	bool m_firstBinding;
};