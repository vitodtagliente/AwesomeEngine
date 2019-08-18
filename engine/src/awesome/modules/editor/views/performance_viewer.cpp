#include "performance_viewer.h"

#include <imgui.h>

namespace awesome
{
	PerformanceViewer::PerformanceViewer()
	{

	}

	PerformanceViewer::~PerformanceViewer()
	{

	}

	void PerformanceViewer::render()
	{
		ImGui::Begin("Performance Viewer");
		ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}