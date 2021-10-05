/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "buffer.h"

class IndexBuffer : public Buffer
{
public:
	IndexBuffer(size_t size, BufferUsageMode mode = BufferUsageMode::Static);
	virtual ~IndexBuffer() override;

	virtual void bind() override;
	virtual void unbind() override;
	virtual void free() override;
	virtual void fillData(void* const data, size_t size) override;
	virtual void fillSubData(void* const data, size_t size, int offset) override;

private:
	unsigned int m_id;
};