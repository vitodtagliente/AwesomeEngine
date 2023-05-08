#include "performance_window.h"

#include <array>
#include <string>
#include <sstream>

#include <awesome/editor/editor_ui.h>
#include <awesome/engine/engine.h>
#include <awesome/graphics/graphics.h>
#include <awesome/scene/entity.h>
#include <awesome/scene/scene_graph.h>

std::string formatMemory(const std::size_t size)
{
	static const std::array<const char*, 7> s_suffixes{ "B", "KB", "MB", "GB", "TB", "PB", "EB" };
	int i = 0; // which suffix to use
	double count = static_cast<double>(size);
	while (count >= 1024 && i < 7)
	{
		++i;
		count /= 1024;
	}

	std::ostringstream s;
	if (count - std::floor(count) == 0.0)
	{
		s << static_cast<int>(count) << " " << s_suffixes[i];
	}
	else
	{
		s << std::fixed << std::setprecision(1) << count << " " << s_suffixes[i];
	}
	return s.str();
}

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
		Entity& root = SceneGraph::instance().root();
		std::size_t size{ root.countChildren() };

		std::ostringstream s;
		s << "SceneGraph::Entities: " << size;
		EditorUI::text(s.str().c_str());
	}

	// Components
	{
		std::ostringstream s;
		s << "Engine::Components: " << Component::metrics().count << " (" <<formatMemory(Component::metrics().size) << ")";
		EditorUI::text(s.str().c_str());
	}

	// Renderer
	{
		std::ostringstream s;
		s << "Graphics::DrawCalls: " << Graphics::instance()->performances.drawCalls;
		EditorUI::text(s.str().c_str());
	}
}