#pragma once

#include <dreamkeeper/core/interfaces/base_buffer.h>
#include <glad/glad.h>
#include <vector>

namespace Dreamkeeper
{
	namespace Core
	{
		struct VertexArrayAttribute
		{
			unsigned int location{ 0 };

			unsigned int type{ GL_FLOAT };
			unsigned int count{ 1 };
			bool should_be_normalized{ false };
			unsigned int relative_offset{ 0 };
			
			VertexArrayAttribute() {};
			VertexArrayAttribute(unsigned int attribute_location);

			void enable();
			void disable();
			void format(unsigned int offset, unsigned int size, bool auto_enable_attribute = true);
		};

		class VertexArrayObject : public BaseBuffer
		{
		private:
			std::vector<VertexArrayAttribute*> attributes{};

		public:
			VertexArrayObject();

			void bind() override;
			void unbind() override;
			void free() override;
			
			void bindAttribute(VertexArrayAttribute* attribute);
			VertexArrayAttribute* findAttribute(unsigned int location);
		};

		typedef VertexArrayObject VAO;
	}
}