#include <awesome/editor/windows/entity_inspector_window.h>

#include <awesome/asset/prefab_asset.h>
#include <awesome/editor/editor_state.h>
#include <awesome/editor/editor_ui.h>
#include <awesome/scene/entity.h>

EntityInspectorWindow::EntityInspectorWindow()
	: Window()
	, m_editorState(EditorState::instance())
{
}

char* const EntityInspectorWindow::getTitle() const
{
	return "Entity Inspector";
}

void EntityInspectorWindow::render()
{
	Entity* const entity = m_editorState->selection.entity;
	if (entity == nullptr)
	{
		return;
	}

	if (entity->state() != Entity::State::Alive)
	{
		m_editorState->unselectEntity();
		return;
	}

	EditorUI::input(*entity);

	EditorUI::separator();

	if (EditorUI::button((EditorUI::Icon::save + " Save Prefab").c_str()))
	{
		EditorUI::Dialog::save("Save Prefab...", ".prefab", [entity](const std::filesystem::path& path) -> void
			{
				Prefab prefab;
				prefab.entity = *entity;
				ResourcerWriter<Prefab>::write(prefab, path);
			}
		);
	}
}