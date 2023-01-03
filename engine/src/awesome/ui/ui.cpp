#include "ui.h"

#include <assert.h>

#include <awesome/graphics/renderer.h>
#include <awesome/entity/world.h>

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

}

void UI::shutdown()
{
	
}

void UI::preRendering()
{
	
}

void UI::render(World* const world, graphics::Renderer2D* const renderer)
{
	const auto previousViewMatrix = renderer->getViewMatrix();
	renderer->setViewMatrix(math::mat4::identity);

	const auto& entities = world->getEntities();
	for (const auto& entity : entities)
	{
		for (const auto& component : entity->getComponents())
		{
			if (!component->enabled) continue;

			if (IUIComponent* const uiComponent = dynamic_cast<IUIComponent*>(component.get()))
			{
				uiComponent->render(renderer);
			}
		}
	}

	renderer->setViewMatrix(previousViewMatrix);
}

void UI::postRendering()
{
	
}

void UI::update(const double)
{
	
}