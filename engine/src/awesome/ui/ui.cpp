#include "ui.h"

#include <assert.h>

#include <awesome/application/canvas.h>
#include <awesome/graphics/renderer.h>
#include <awesome/entity/world.h>

#include "components/components.h"
#include "ui_component.h"

UI* UI::s_instance{ nullptr };

UI::UI()
	: ApplicationModule()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

void UI::startup()
{
	m_renderer = std::make_unique<graphics::Renderer2D>(0, 0);
}

void UI::shutdown()
{
	
}

void UI::preRendering()
{
	static const bool clear = false;
	m_renderer->begin(clear);
}

void UI::render(World* const world, graphics::Renderer2D* const)
{
	const auto& canvas = Canvas::instance();
	m_renderer->setViewport(canvas.getWidth(), canvas.getHeight());
	float w = static_cast<float>(canvas.getWidth()) / 2 / 32;
	float h = static_cast<float>(canvas.getHeight()) / 2 / 32;
	m_renderer->setProjectionMatrix(math::mat4::orthographic(-w, w, -h, h, -1, 1000));

	const auto& entities = world->getEntities();
	for (const auto& entity : entities)
	{
		for (const auto& component : entity->getComponents())
		{
			if (!component->enabled) continue;

			if (IUIComponent* const uiComponent = dynamic_cast<IUIComponent*>(component.get()))
			{
				uiComponent->render(m_renderer.get());
			}
		}
	}
}

void UI::postRendering()
{
	m_renderer->flush();
}

void UI::update(const double)
{
	
}