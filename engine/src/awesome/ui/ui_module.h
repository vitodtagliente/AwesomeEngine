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
		virtual void update_implementation() override;
	};
}