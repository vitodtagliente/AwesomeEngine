#pragma once

#include <awesome/engine/engine.h>

namespace awesome
{
	class Editor;

	class EditorModule : public Engine::Module
	{
	public:

		EditorModule();
		~EditorModule();

	protected:

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
		virtual void update_implementation() override;
		virtual void pre_rendering_implementation() override;
		virtual void render_implementation() override;
		virtual void post_rendering_implementation() override;

	private:

		// editor instance
		Editor* m_editor;
	};
}