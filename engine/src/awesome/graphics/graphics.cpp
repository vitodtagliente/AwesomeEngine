#include "graphics.h"

#include <assert.h>

#include <awesome/application/canvas.h>
#include <awesome/component/camera_component.h>
#include <awesome/entity/world.h>

#include "graphics_component.h"
#include "renderer.h"

Graphics* Graphics::s_instance{ nullptr };

Graphics::Graphics()
	: ApplicationModule()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

void Graphics::startup()
{
	renderer = std::make_unique<graphics::Renderer2D>(0, 0);
}

void Graphics::shutdown()
{
}

void Graphics::preRendering()
{
	renderer->begin();
	const auto& canvas = Canvas::instance();
	renderer->setViewport(canvas.getWidth(), canvas.getHeight());

	CameraComponent* const camera = CameraComponent::main();
	if (camera)
	{
		renderer->setClearColor(camera->color);
		renderer->setProjectionMatrix(camera->getData().getProjectionMatrix(canvas.getWidth(), canvas.getHeight()));
		renderer->setViewMatrix(camera->getData().getViewMatrix());
	}
}

void Graphics::render()
{
	for (const auto& entity : World::instance().getEntities())
	{
		for (const auto& component : entity->getComponents())
		{
			if (!component->enabled) continue;


			if (graphics::IGraphicsComponent* const graphicsComponent = dynamic_cast<graphics::IGraphicsComponent*>(component.get()))
			{
				graphicsComponent->render(renderer.get());
			}
		}
	}
}

void Graphics::postRendering()
{	
	performances.drawCalls = renderer->flush();
}