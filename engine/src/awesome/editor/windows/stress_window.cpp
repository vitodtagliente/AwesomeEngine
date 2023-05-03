#include "stress_window.h"

#include <awesome/editor/editor_ui.h>
#include <awesome/math/algorithm.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/scene_graph.h>

char* const StressWindow::getTitle() const
{
	return "Stress";
}

void StressWindow::render()
{
	EditorUI::input("Prefab", m_prefab);

	if (!m_prefab.ready()) return;

	EditorUI::separator();
	EditorUI::input("Quantity", m_quantity);
	EditorUI::input("Random Position", m_randomPosition);
	EditorUI::hint("True to spawn the prefabs in random positions");
	if (m_randomPosition)
	{
		EditorUI::input("Min Position", m_minPosition);
		EditorUI::input("Max Position", m_maxPosition);
	}
	EditorUI::newLine();
	if (EditorUI::button("Spawn"))
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