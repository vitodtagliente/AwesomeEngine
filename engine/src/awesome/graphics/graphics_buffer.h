/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <cstddef>
#include <vector>

struct GraphicsBufferElement
{
	enum class Type
	{
		Char,
		Float,
		Integer,
		UnsignedInteger
	};

	// the number of elements
	unsigned int count;
	// the type
	Type type;
	// normalized
	bool normalized;
	// size
	std::size_t size;

	GraphicsBufferElement(
		const unsigned int count,
		const Type type,
		const std::size_t size,
		const bool normalized = false
	);
};

class GraphicsBufferLayout
{
public:

	GraphicsBufferLayout();

	inline std::size_t getStride() const { return m_stride; }
	inline const std::vector<GraphicsBufferElement>& getElements() const { return m_elements; }

	void push(const GraphicsBufferElement& element);
	void clear();

private:

	// buffer elements
	std::vector<GraphicsBufferElement> m_elements;
	// layout stride
	std::size_t m_stride;
};

class GraphicsBuffer
{
public:

	enum class Type
	{
		Vertex,
		Index
	};

	GraphicsBuffer(const Type type, const void* const data, const std::size_t size);
	virtual ~GraphicsBuffer();

	inline Type type() const { return m_type; }
	inline std::size_t size() const { return m_size; }

	void bind();
	void unbind();

	// buffer layout
	GraphicsBufferLayout layout;

	inline unsigned int id() const { return m_id; }

private:

	// buffer id
	unsigned int m_id;
	// native buffer type
	unsigned int m_nativeType;
	// buffer type
	Type m_type;
	// buffer size
	std::size_t m_size;

};