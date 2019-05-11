#pragma once 

#include "../vertex_array.h"

namespace awesome
{ 
	class VertexArrayGL final : public VertexArray
	{
	public:

		VertexArrayGL();
		~VertexArrayGL();

		virtual void bind() override;
		virtual void unbind() override;
		
		virtual void add(VertexBuffer* const t_buffer, VertexBufferLayout* const t_layout) override;
	};
}