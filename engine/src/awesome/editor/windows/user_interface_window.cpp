#include "user_interface_window.h"

#include <awesome/core/string_util.h>
#include <awesome/editor/editor_state.h>
#include <awesome/editor/editor_ui.h>
#include <awesome/ui/control.h>
#include <awesome/ui/ui_graph.h>

UserInterfaceWindow::UserInterfaceWindow()
	: Window()
	, m_editorState(EditorState::instance())
{
}

char* const UserInterfaceWindow::getTitle() const
{
	return "UI";
}

void reparentControl(const uuid& id, Control* parent)
{
	if (id == parent->id()) return;

	Control* const draggingControl = UIGraph::instance().root().findChildById(id);
	if (draggingControl == nullptr
		|| parent->findChildById(id, false) != nullptr)
		return;

	draggingControl->parent()->moveChild(parent, id);
}

void UserInterfaceWindow::render()
{
	Control* const selectedControl = m_editorState->selection.control;
	Control& root = UIGraph::instance().root();

	if (EditorUI::button(EditorUI::Icon::plus.c_str()))
	{
		Control* const entity = root.addChild();
		entity->name = entity->id().value;
	}

	EditorUI::sameLine();
	if (EditorUI::search(m_filter))
	{
		m_editorState->unselectControl();
	}

	EditorUI::Child::begin("SceneContent");

	EditorUI::Tree::openNextItem();
	const bool open = EditorUI::Tree::begin("ui", false);
	EditorUI::DragDrop::end("Control::ChangeParent", [this, &root](void* const data, const size_t) -> void { reparentControl(*(const uuid*)data, &root); });

	if (open)
	{
		for (auto it = root.children().begin(); it != root.children().end(); ++it)
		{
			const auto& control = *it;
			renderControl(control.get(), selectedControl);
		}
		EditorUI::Tree::end();
	}

	EditorUI::Child::end();

	// reset the entity selection once clicked in the entities area
	if (EditorUI::Input::isItemHovered() && EditorUI::Input::isMouseClicked())
	{
		m_editorState->unselectControl();
	}
}

void UserInterfaceWindow::update(double)
{
	if (!hasFocus()) return;

	Control* const selectedControl = m_editorState->selection.control;
	if (selectedControl != nullptr && EditorUI::Input::isKeyPressed(KeyCode::Delete))
	{
		deleteControl(selectedControl);
	}
}

void UserInterfaceWindow::deleteControl(Control* const control)
{
	const uuid id = control->id();
	control->queue_destroy();
	const auto& controls = UIGraph::instance().root().children();
	if (!controls.empty())
	{
		if (controls[0]->id() == id)
		{
			if (controls.size() > 1)
			{
				m_editorState->select(controls[1].get());
			}
			else
			{
				m_editorState->unselectControl();
			}
		}
		else
		{
			m_editorState->select(controls[0].get());
		}
	}
	else
	{
		m_editorState->unselectControl();
	}
}

void UserInterfaceWindow::renderControl(Control* const control, Control* const selectedControl)
{
	if (control == nullptr) return;
	
	const std::string name = control->name + "##control" + control->id().value;
	if (control->hasChildren())
	{
		if (m_filter.empty())
		{
			const bool forceOpen = selectedControl && control->findChildById(selectedControl->id());
			if (forceOpen)
			{
				EditorUI::Tree::openNextItem();
			}

			const bool open = EditorUI::Tree::begin(name.c_str(), control == selectedControl);
			if (EditorUI::Tree::isClicked())
			{
				m_editorState->select(control);
			}

			EditorUI::DragDrop::begin("Control::ChangeParent", control->name.c_str(), (void*)(&control->id()), sizeof(uuid));
			EditorUI::DragDrop::end("Control::ChangeParent", [this, control](void* const data, const size_t) -> void { reparentControl(*(const uuid*)data, control); });

			if (open)
			{
				for (const auto& child : control->children())
				{
					renderControl(child.get(), selectedControl);
				}
				EditorUI::Tree::end();
			}
		}
		else
		{
			if (StringUtil::contains(control->name, m_filter, StringUtil::CompareMode::IgnoreCase))
			{
				if (EditorUI::selectable(name.c_str(), control == selectedControl))
				{
					m_editorState->select(control);
				}

				EditorUI::DragDrop::begin("Control::ChangeParent", control->name.c_str(), (void*)(&control->id()), sizeof(uuid));
				EditorUI::DragDrop::end("Control::ChangeParent", [this, control](void* const data, const size_t) -> void { reparentControl(*(const uuid*)data, control); });
			}

			for (const auto& child : control->children())
			{
				renderControl(child.get(), selectedControl);
			}
		}		
	}
	else
	{
		if (!m_filter.empty() && !StringUtil::contains(control->name, m_filter, StringUtil::CompareMode::IgnoreCase)) return;

		if (EditorUI::selectable(name.c_str(), control == selectedControl))
		{
			m_editorState->select(control);
		}

		EditorUI::DragDrop::begin("Control::ChangeParent", control->name.c_str(), (void*)(&control->id()), sizeof(uuid));
		EditorUI::DragDrop::end("Control::ChangeParent", [this, control](void* const data, const size_t) -> void { reparentControl(*(const uuid*)data, control); });
	}
}
