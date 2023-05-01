#include "stress_window.h"

#include <awesome/editor/widgets/form_layout.h>
#include <awesome/math/algorithm.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/scene_graph.h>

char* const StressWindow::getTitle() const
{
	return "Stress";
}

void StressWindow::render()
{
	FormLayout::asset("Prefab", m_prefab);

	if (!m_prefab.ready()) return;

	FormLayout::separator();
	FormLayout::input("Quantity", m_quantity);
	FormLayout::input("Random Position", m_randomPosition);
	FormLayout::hint("True to spawn the prefabs in random positions");
	if (m_randomPosition)
	{
		FormLayout::input("Min Position", m_minPosition);
		FormLayout::input("Max Position", m_maxPosition);
	}
	FormLayout::newLine();
	if (FormLayout::button("Spawn"))
	{
		Entity* const root = SceneGraph::instance().root();
		for (int i = 0; i < m_quantity; ++i)
		{
			std::unique_ptr<Entity> entity = std::make_unique<Entity>(m_prefab.resource->entity);
			if (m_randomPosition)
			{
				entity->transform.position = math::vec3(
					math::random(m_minPosition.x, m_maxPosition.x),
					math::random(m_minPosition.y, m_maxPosition.y),
					math::random(m_minPosition.z, m_maxPosition.z)
				);
			}
			root->addChild(std::move(entity));
		}
	}
}