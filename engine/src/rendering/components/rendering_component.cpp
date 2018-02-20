#include <awesome/rendering/components/rendering_component.h>
#include <awesome/rendering/objects/camera.h>

namespace Awesome
{
	namespace Rendering
	{
		void RenderingComponent::render()
		{
			/*
			if (material != nullptr && material->program != nullptr)
			{
				auto program = material->program;
				auto camera = Camera::main();
				program->use();
				program->setMat4("projection", camera->getProjection());
				program->setMat4("view", camera->getView());
				auto model = owner()->transform.get();
				program->setMat4("model", model);
			}
			*/
		}
	}
}