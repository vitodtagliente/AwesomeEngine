#include "inspector_window.h"

#include <awesome/editor/state.h>
#include <awesome/editor/windows/inspectors/entity_inspector.h>
#include <awesome/editor/windows/inspectors/image_inspector.h>
#include <awesome/editor/windows/inspectors/prefab_inspector.h>
#include <awesome/editor/windows/inspectors/scene_inspector.h>
#include <awesome/editor/windows/inspectors/sprite_animation_inspector.h>
#include <awesome/editor/windows/inspectors/sprite_inspector.h>
#include <awesome/editor/windows/inspectors/text_inspector.h>

namespace editor
{
	InspectorWindow::InspectorWindow()
		: Window()
		, m_inspectors()
	{
	}

	void InspectorWindow::init()
	{
		m_inspectors.push_back(std::make_unique<EntityInspector>());
		m_inspectors.push_back(std::make_unique<ImageInspector>());
		m_inspectors.push_back(std::make_unique<PrefabInspector>());
		m_inspectors.push_back(std::make_unique<SceneInspector>());
		m_inspectors.push_back(std::make_unique<SpriteAnimationInspector>());
		m_inspectors.push_back(std::make_unique<SpriteInspector>());
		m_inspectors.push_back(std::make_unique<TextInspector>());
	}

	void InspectorWindow::update(const double deltaTime)
	{
		const auto& selection = State::instance().selection;
		if (selection.has_value())
		{
			for (const auto& inspector : m_inspectors)
			{
				if (inspector->canInspect(*selection))
				{
					inspector->update(*selection, deltaTime);
					break;
				}
			}
		}
	}

	void InspectorWindow::render()
	{
		const auto& selection = State::instance().selection;
		if (selection.has_value())
		{
			for (const auto& inspector : m_inspectors)
			{
				if (inspector->canInspect(*selection))
				{
					inspector->inspect(*selection);
					break;
				}
			}
		}
	}

	REFLECT_WINDOW(InspectorWindow)
}