#pragma once

#include <cstddef>
#include <vector>
#include "../core/types.h"

namespace awesome
{
	struct VertexBufferElement
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

		VertexBufferElement(
			const unsigned int t_count,
			const Type t_type,
			const std::size_t t_size,
			const bool t_normalized = false
		);			
	};

	class VertexBufferLayout
	{
	public:

		VertexBufferLayout();

		inline std::size_t getStride() const { return m_stride; }
		inline const std::vector<VertexBufferElement>& getElements() const { return m_elements; }

		void push(const VertexBufferElement& t_element);

	private:

		// buffer elements
		std::vector<VertexBufferElement> m_elements;
		// layout stride
		std::size_t m_stride;
	};
}