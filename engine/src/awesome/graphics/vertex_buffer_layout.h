#pragma once

#include <cstddef>
#include <vector>
#include "../core/types.h"

namespace awesome
{
	struct VertexBufferElement
	{
		// the number of elements
		unsigned int count;
		// the type
		unsigned int type;
		// normalized
		bool normalized;
		// size
		std::size_t size;

		VertexBufferElement(
			const unsigned int t_count,
			const unsigned int t_type,
			const std::size_t t_size,
			const bool t_normalized = false
		)
			: count(t_count)
			, type(t_type)
			, normalized(t_normalized)
		{
			size = t_count * t_size;
		}
	};

	class VertexBufferLayout
	{
	public:

		VertexBufferLayout()
			: m_elements()
			, m_stride(0)
		{

		}

		inline std::size_t getStride() const { return m_stride; }
		inline const std::vector<VertexBufferElement>& getElements() const { return m_elements; }

		template <typename T>
		void push(unsigned int t_count) {
			static_assert(false);
		}

		template <>
		void push<float>(unsigned int t_count) {
			VertexBufferElement element(t_count, float_t, sizeof(float));
			m_elements.push_back(element);
			m_stride += element.size;
		}

		template <>
		void push<unsigned int>(unsigned int t_count) {
			VertexBufferElement element(t_count, uint_t, sizeof(unsigned int));
			m_elements.push_back(element);
			m_stride += element.size;
		}

		template <>
		void push<unsigned char>(unsigned int t_count) {
			VertexBufferElement element(t_count, ubyte_t, sizeof(unsigned int));
			m_elements.push_back(element);
			m_stride += element.size;
		}

	protected:

		// buffer elements
		std::vector<VertexBufferElement> m_elements;
		// layout stride
		std::size_t m_stride;

		unsigned int float_t;
		unsigned int uint_t;
		unsigned int ubyte_t;
	};
}