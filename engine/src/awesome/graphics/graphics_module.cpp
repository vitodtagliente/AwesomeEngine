#include "graphics_module.h"

#include <awesome/application/canvas.h>
#include <awesome/component/camera_component.h>
#include <awesome/entity/world.h>

#include "context.h"
#include "graphics_component.h"
#include "renderer.h"

namespace graphics
{
	void Module::startup()
	{

	}

	void Module::shutdown()
	{
	}

	void Module::preRendering()
	{
		Context::instance().renderer.begin();
	}

	void Module::render(World* const world, graphics::Renderer2D* const renderer)
	{
		const auto& canvas = Canvas::instance();
		renderer->setViewport(canvas.getWidth(), canvas.getHeight());

		CameraComponent* const camera = CameraComponent::main();
		if (camera)
		{
			renderer->setClearColor(camera->color);
			renderer->setProjectionMatrix(camera->getData().getProjectionMatrix(canvas.getWidth(), canvas.getHeight()));
			renderer->setViewMatrix(camera->getData().getViewMatrix());
		}		

		const auto& entities = world->getEntities();
		for (const auto& entity : entities)
		{
			for (const auto& component : entity->getComponents())
			{
				if (!component->enabled) continue;


				if (graphics::IGraphicsComponent* const graphicsComponent = dynamic_cast<graphics::IGraphicsComponent*>(component.get()))
				{
					graphicsComponent->render(renderer);
				}
			}
		}
	}

	void Module::postRendering()
	{
		Context& context = Context::instance();
		context.m_drawCalls = context.renderer.flush();
	}
}