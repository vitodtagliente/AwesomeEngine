#pragma once

#include <awesome/graphics/graphics_buffer.h>

namespace awesome
{
	class GraphicsBufferGL final : public GraphicsBuffer
	{
	public:

		GraphicsBufferGL(const Type t_type, const void* const t_data, const std::size_t t_size);
		virtual ~GraphicsBufferGL() override;

		virtual void bind() override;
		virtual void unbind() override;
	
		inline unsigned int id() const { return m_id; }

	private:

		// buffer id
		unsigned int m_id;
		// native buffer type
		unsigned int m_nativeType;
	};
}