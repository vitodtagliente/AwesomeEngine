/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>

#include "buffer.h"

namespace graphics
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

		// the name of the element
		std::string name;
		// the type
		Type type;
		// num of components
		std::size_t size;
		// if normalized
		bool normalized;
		// if per instance
		bool instanced;

		VertexBufferElement(
			const std::string& name,
			Type type,
			std::size_t size,
			bool normalized = true,
			bool instanced = false
		)
			: name(name)
			, type(type)
			, size(size)
			, normalized(normalized)
			, instanced(instanced)
		{}
	};

	class VertexBufferLayout
	{
	public:
		VertexBufferLayout()
			: m_elements()
			, m_stride(0)
		{}

		inline std::size_t getStride() const { return m_stride; }
		inline const std::vector<VertexBufferElement>& getElements() const { return m_elements; }

		void push(const VertexBufferElement& element);
		void clear();

		unsigned int startingIndex = 0;

	private:
		// buffer elements
		std::vector<VertexBufferElement> m_elements;
		// layout stride
		std::size_t m_stride;
	};

	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(size_t size, BufferUsageMode mode = BufferUsageMode::Static);
		virtual ~VertexBuffer() override;

		virtual void bind() override;
		virtual void unbind() override;
		virtual void free() override;
		virtual void fillData(void* const data, size_t size) override;
		virtual void fillSubData(void* const data, size_t size, int offset) override;

		void activateLayout();

		VertexBufferLayout layout;

	private:
		unsigned int m_id;
	};
}