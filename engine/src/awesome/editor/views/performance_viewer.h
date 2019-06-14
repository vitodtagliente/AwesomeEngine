#pragma once

#include <awesome/editor/editor_view.h>

namespace awesome
{
	class PerformanceViewer : public EditorView
	{
	public:

		PerformanceViewer();
		~PerformanceViewer();

		virtual void render() override;

	};
}