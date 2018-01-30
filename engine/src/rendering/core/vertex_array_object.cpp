#include <dreamkeeper/core/vertex_array_object.h>
#include <glad/glad.h>

namespace Dreamkeeper
{
	namespace Core
	{

		VertexArrayObject::VertexArrayObject()
		{

		}

		void VertexArrayObject::bind()
		{
			if (id == 0)
				glGenVertexArrays(1, &id);
			glBindVertexArray(id);
		}

		void VertexArrayObject::unbind()
		{
			glBindVertexArray(0);
		}

		void VertexArrayObject::free()
		{
			glDeleteVertexArrays(1, &id);
		}

		void VertexArrayObject::bindAttribute(VertexArrayAttribute* attribute)
		{
			attributes.push_back(attribute);
		}

		Dreamkeeper::Core::VertexArrayAttribute* VertexArrayObject::findAttribute(unsigned int location)
		{
			for (std::vector<VertexArrayAttribute*>::iterator it = attributes.begin(); it != attributes.end(); ++it)
				if ((*it)->location == location)
					return *it;
			return nullptr;
		}

		VertexArrayAttribute::VertexArrayAttribute(unsigned int attribute_location)
		{
			this->location = attribute_location;
		}

		void VertexArrayAttribute::enable()
		{
			glEnableVertexAttribArray(location);
		}

		void VertexArrayAttribute::disable()
		{
			glDisableVertexAttribArray(location);
		}

		void VertexArrayAttribute::format(unsigned int offset, unsigned int size, bool auto_enable_attribute /*= true*/)
		{
			glVertexAttribPointer(location, count, type, should_be_normalized, size, (void*)offset);
			if (auto_enable_attribute)
				enable();
		}
	}
}