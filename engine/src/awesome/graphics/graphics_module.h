/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/application/application_module.h>

namespace graphics
{
	class Module : public ApplicationModule
	{
	public:
		Module() = default;

		virtual void startup() override;
		virtual void shutdown() override;
		virtual void preRendering() override;
		virtual void postRendering() override;
	};
}