#include "inspector_window.h"

#include "inspectors/entity_inspector.h"
#include "inspectors/image_inspector.h"
#include "inspectors/prefab_inspector.h"
#include "inspectors/sprite_animation_inspector.h"
#include "inspectors/sprite_inspector.h"
#include "inspectors/text_inspector.h"

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
		m_inspectors.push_back(std::make_unique<SpriteAnimationInspector>());
		m_inspectors.push_back(std::make_unique<SpriteInspector>());
		m_inspectors.push_back(std::make_unique<TextInspector>());
	}

	void InspectorWindow::update(const double deltaTime)
	{
		const auto& selection = getState()->selection;
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
		const auto& selection = getState()->selection;
		if (selection.has_value())
		{
			for (const auto& inspector : m_inspectors)
			{
				if (inspector->canInspect(*selection))
				{
					inspector->inspect(*selection, getState()->workPath);
					break;
				}
			}
		}
	}

	REFLECT_EDITOR(InspectorWindow)
}