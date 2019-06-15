#include "scene_viewer.h"

#include <imgui.h>
#include <string>
#include <vector>
#include <awesome/scene/world.h>
#include <awesome/scene/object.h>
#include "object_viewer.h"
#include <awesome/editor/editor.h>

namespace awesome
{
	SceneViewer::SceneViewer()
		: m_selection_index()
		, m_selection_object()
	{
	}
	
	SceneViewer::~SceneViewer()
	{
	}

	void SceneViewer::render()
	{
		static auto vector_getter = [](void* vec, int idx, const char** out_text)
		{
			auto& vector = *static_cast<std::vector<std::string>*>(vec);
			if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
			*out_text = vector.at(idx).c_str();
			return true;
		};

		if (World * const world  = World::instance())
		{
			std::vector<std::string> items{};
			for (Object* const object : world->getObjects())
			{
				items.push_back({ object->name.data() });
			}

			ImGui::Begin("Scene Viewer");
			if (ImGui::ListBox(
				"##scene_viewer",
				&m_selection_index,
				vector_getter,
				static_cast<void*>(&items),
				items.size(),
				4))
			{
				Object* const new_selection = world->getObjects()[m_selection_index];
				if (m_selection_object != new_selection)
				{
					m_selection_object = new_selection;
					if (ObjectViewer * object_viewer = Editor::instance()->getView<ObjectViewer>())
					{
						object_viewer->selection = new_selection;
					}
				}
			}
			ImGui::End();

		}
	}
}