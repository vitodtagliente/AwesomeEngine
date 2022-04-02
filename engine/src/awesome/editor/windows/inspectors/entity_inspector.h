/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <awesome/editor/windows/inspector_window.h>

namespace editor
{
	class EntityInspector : public InspectorWindow::Inspector
	{
	public:
		EntityInspector();

		virtual bool canInspect(const State::Selection& selection) override;
		virtual void inspect(const State::Selection& selection, const std::filesystem::path& path) override;

	private:
		class Entity* m_previousSelecytedEntity;
		std::string m_filename;
	};
}