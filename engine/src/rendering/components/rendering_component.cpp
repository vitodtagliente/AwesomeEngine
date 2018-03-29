#include <awesome/rendering/components/rendering_component.h>
#include <awesome/rendering/objects/camera.h>

namespace Awesome
{
	void RenderingComponent::render()
	{
		if (material != nullptr && material->program != nullptr)
		{
			auto program = material->program;
			auto camera = Camera::main();
			if (camera != nullptr)
			{
				program->use();
				/* setup camera matrices */
				program->setMat4("projection", camera->getProjection());
				program->setMat4("view", camera->getView());
				/* setup model matrix */
				program->setMat4("model", owner()->transform.get());
			}
		}
	}
}