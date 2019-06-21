#include "graphics_module.h"

#include <vector>
#include "graphics_api.h"
#include "renderer.h"
#include "components/rendering_component.h"
#include "../scene/world.h"
#include "../scene/object.h"

namespace awesome
{
	GraphicsModule::GraphicsModule()
		: m_api()
		, m_renderer()
	{
	}

	GraphicsModule::~GraphicsModule()
	{
	}

	bool GraphicsModule::startup_implementation()
	{
		m_api = createAPI();
		if (m_api->startup())
		{
			m_renderer = createRenderer(m_api);
			return true;
		}
		return false;
	}
	
	void GraphicsModule::shutdown_implementation()
	{
		m_api->shutdown();
	}
	
	void GraphicsModule::update_implementation()
	{
	}

	void GraphicsModule::pre_rendering_implementation()
	{
		for (Object* const object : World::instance()->getObjects())
		{
			for (RenderingComponent* rendering_component : object->getComponents<RenderingComponent>())
			{
				rendering_component->push_data(m_renderer);
			}
		}
	}

	void GraphicsModule::render_implementation()
	{
		m_renderer->render();
	}

	void GraphicsModule::post_rendering_implementation()
	{
	}
}