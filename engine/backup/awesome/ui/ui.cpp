#include "ui.h"

#include <assert.h>

#include <awesome/entity/entity.h>
#include <awesome/entity/world.h>

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

void UI::render()
{
	for (const auto& entity : World::instance().getEntities())
	{
		if (entity->getState() != Entity::State::Alive) continue;

		for (const auto& component : entity->getComponents())
		{
			if (!component->enabled) continue;

			// component->render(renderer.get());
		}
	}
}

void UI::postRendering()
{

}

void UI::update(const double)
{
	
}