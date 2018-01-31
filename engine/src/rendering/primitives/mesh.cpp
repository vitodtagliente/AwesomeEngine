#include <awesome/rendering/primitives/mesh.h>
#include <glad/glad.h>

namespace Awesome
{
	namespace Rendering
	{
		void Mesh::init() 
		{
			
		}

		void Mesh::draw()
		{

		}

		void Mesh::bind() 
		{
			glBindVertexArray(vao);
		}

		void Mesh::unbind()
		{
			glBindVertexArray(0);
		}
	}
}