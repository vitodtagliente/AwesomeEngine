#include "performance_window.h"

#include <string>
#include <sstream>

#include <awesome/editor/editor_ui.h>
#include <awesome/engine/engine.h>
#include <awesome/graphics/graphics.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/scene_graph.h>

char* const PerformanceWindow::getTitle() const
{
	return "Performance";
}

void PerformanceWindow::render()
{
	// FPS
	{
		const Engine::Stats& stats = Engine::instance().getStats();

		std::ostringstream s;
		s << "Engine::FPS: " << stats.framerate << " (" << std::round(1000.0f / stats.framerate) << " ms/frame)";
		EditorUI::text(s.str().c_str());
	}

	// Entities
	{
		Entity* const root = SceneGraph::instance().root();
		std::size_t size{ root->countChildren() };

		std::ostringstream s;
		s << "SceneGraph::Entities: " << size;
		EditorUI::text(s.str().c_str());
	}

	// Renderer
	{
		std::ostringstream s;
		s << "Graphics::DrawCalls: " << Graphics::instance()->performances.drawCalls;
		EditorUI::text(s.str().c_str());
	}
}