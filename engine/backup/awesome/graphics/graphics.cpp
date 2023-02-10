#include "graphics.h"

#include <assert.h>

#include <awesome/application/canvas.h>
#include <awesome/component/camera_component.h>
#include <awesome/entity/world.h>

#include "context.h"
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
	m_context = std::make_unique<graphics::Context>();
	if (m_context->initialize() != graphics::Context::State::Initialized)
	{
		return;
	}
	renderer = std::make_unique<graphics::Renderer>();
	if (!renderer->init(m_context.get()))
	{
		return;
	}
}

void Graphics::shutdown()
{
}

void Graphics::preRendering()
{
	const auto& canvas = Canvas::instance();
	renderer->setViewport(canvas.getWidth(), canvas.getHeight());

	CameraComponent* const camera = CameraComponent::main();
	if (camera)
	{
		renderer->clear(camera->color);
		renderer->setProjectionMatrix(camera->getData().getProjectionMatrix(canvas.getWidth(), canvas.getHeight()));
		renderer->setViewMatrix(camera->getData().getViewMatrix());
	}
	else
	{
		renderer->clear(graphics::Color::Black);
	}
}

void Graphics::render()
{
	for (const auto& entity : World::instance().getEntities())
	{
		if (entity->getState() != Entity::State::Alive) continue;

		for (const auto& component : entity->getComponents())
		{
			if (!component->enabled) continue;

			component->render(renderer.get());
		}
	}
}

void Graphics::postRendering()
{	
	renderer->flush();
	performances.drawCalls = renderer->stats.drawCalls;
}