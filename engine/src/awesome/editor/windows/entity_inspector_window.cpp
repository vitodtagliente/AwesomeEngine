#include <awesome/editor/windows/entity_inspector_window.h>

#include <awesome/asset/prefab_asset.h>
#include <awesome/editor/editor_state.h>
#include <awesome/editor/text_icon.h>
#include <awesome/editor/widgets/dialog_layout.h>
#include <awesome/editor/widgets/entity_layout.h>
#include <awesome/editor/widgets/form_layout.h>
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

	EntityLayout::input(*entity);

	FormLayout::separator();

	if (FormLayout::button(TextIcon::save(" Save Prefab").c_str()))
	{
		DialogLayout::save("Save Prefab...", ".prefab", [entity](const std::filesystem::path& path) -> void
			{
				PrefabAsset prefab;
				prefab.data.entity = *entity;
				prefab.save(path);
			}
		);
	}
}