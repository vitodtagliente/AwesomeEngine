#include <awesome/rendering/components/mesh_rendering_component.h>
#include <awesome/rendering/primitives/mesh.h>
#include <glad/glad.h>

namespace Awesome
{
	namespace Rendering
	{
		void MeshRenderingComponent::init()
		{
			if (mesh != nullptr)
				mesh->init();
		}

		void MeshRenderingComponent::update(float delta_time)
		{

		}

		void MeshRenderingComponent::render()
		{
			if (mesh != nullptr)
			{
				mesh->bind();
				if(mesh->indices.size() > 0)
					glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0); 
				else glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());
			}
		}
	}
}