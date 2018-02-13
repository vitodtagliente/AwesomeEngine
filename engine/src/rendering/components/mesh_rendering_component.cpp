#include <awesome/rendering/components/mesh_rendering_component.h>
#include <awesome/rendering/primitives/mesh.h>

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
				mesh->draw();
		}
	}
}