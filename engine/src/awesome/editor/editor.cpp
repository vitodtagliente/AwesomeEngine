#include "editor.h"

#include "editor_view.h"
#include "views/performance_viewer.h"
#include "views/scene_viewer.h"
#include "views/object_viewer.h"

namespace awesome
{
	Editor::Editor()
		: enabled(true)
		, m_views()
	{
	}

	Editor::~Editor()
	{
	}

	void Editor::initialize()
	{
		show<PerformanceViewer>();
		show<SceneViewer>();
		show<ObjectViewer>();
	}

	void Editor::render()
	{
		for (EditorView* const view : m_views)
		{
			if (view->visible)
			{
				view->render();
			}
		}
	}


}