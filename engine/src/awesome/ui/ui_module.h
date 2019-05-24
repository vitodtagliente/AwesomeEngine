#pragma once

#include "../core/singleton.h"
#include "../engine/module.h"

namespace awesome
{
	class UIModule : public Module, public Singleton<UIModule>
	{
	public:

		UIModule();
		~UIModule();

	protected:

		virtual bool startup_implementation() override;
		virtual void shutdown_implementation() override;
		virtual void pre_rendering_implementation() override;
		virtual void render_implementation() override;
		virtual void post_rendering_implementation() override;
	};
}