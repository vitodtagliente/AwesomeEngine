#pragma once

#include <awesome/editor/editor_element.h>

namespace awesome
{
	class SceneViewer : public EditorElement
	{
	public:

		SceneViewer();
		~SceneViewer();

		virtual void init() override;
		virtual void gui() override;
		virtual void uninit() override;

	private:

		// world instance
		class World* m_world;

	};
}