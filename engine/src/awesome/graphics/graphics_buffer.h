#pragma once

#include <cstddef>
#include <vector>

namespace awesome
{
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
			const unsigned int t_count,
			const Type t_type,
			const std::size_t t_size,
			const bool t_normalized = false
		);
	};

	class GraphicsBufferLayout
	{
	public:

		GraphicsBufferLayout();

		inline std::size_t getStride() const { return m_stride; }
		inline const std::vector<GraphicsBufferElement>& getElements() const { return m_elements; }

		void push(const GraphicsBufferElement& t_element);
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

		GraphicsBuffer(const Type t_type, const void * const t_data, const std::size_t t_size);
		virtual ~GraphicsBuffer();

		inline Type type() const { return m_type; }
		inline std::size_t size() const { return m_size; }

		virtual void bind() = 0;
		virtual void unbind() = 0;

		// buffer layout
		GraphicsBufferLayout layout;

	protected:

		// buffer type
		Type m_type;
		// buffer size
		std::size_t m_size;

	};
}