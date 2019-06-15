#pragma once

#include <awesome/core/event.h>
#include <awesome/editor/editor_view.h>

namespace awesome
{
	class Object;

	class SceneViewer : public EditorView
	{
	public:

		SceneViewer();
		~SceneViewer();

		virtual void render() override;

		// selection event
		BaseEvent<void, Object*> onSelectedObjectChanged;

	private:

		// current selection
		int m_selection_index;
		// last selected object
		Object* m_selection_object;

	};
}