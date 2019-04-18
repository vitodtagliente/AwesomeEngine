#pragma once

#include <cstddef>
#include <vector>
#include "../types.h"

namespace awesome
{
	struct VertexBufferElement
	{
		// the number of elements
		uint count;
		// the type
		uint type;
		// normalized
		bool normalized;
		// size
		std::size_t size;

		VertexBufferElement(
			const uint t_count,
			const uint t_type,
			const std::size_t t_size,
			const bool t_normalized = false
		);
	};

	class VertexBufferLayout
	{
	public:

		VertexBufferLayout();
		
		std::size_t getStride() const;
		const std::vector<VertexBufferElement>& getElements() const;

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

	private:

		// buffer elements
		std::vector<VertexBufferElement> m_elements;
		// layout stride
		std::size_t m_stride;

		static const uint float_t;
		static const uint uint_t;
		static const uint ubyte_t;
	};
}