#pragma once

#include <awesome/editor/editor_view.h>

namespace awesome
{
	class SceneViewer : public EditorView
	{
	public:

		SceneViewer();
		~SceneViewer();

		virtual void init() override;
		virtual void render() override;
		virtual void uninit() override;

	private:

		// world instance
		class World* m_world;

	};
}