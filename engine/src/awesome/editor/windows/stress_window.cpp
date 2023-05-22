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

	EditorUI::input("Quantity", m_quantity);
	EditorUI::slider("Range", 0.f, 90.f, m_range);
	if (EditorUI::button("Spawn"))
	{
		Entity& root = SceneGraph::instance().root();
		for (int i = 0; i < m_quantity; ++i)
		{
			std::unique_ptr<Entity> entity = std::make_unique<Entity>(m_prefab.resource->entity);
			entity->transform.position = math::vec3(math::random(-m_range, m_range), math::random(-m_range, m_range), 0.f);
			root.addChild(std::move(entity));
		}
	}
}