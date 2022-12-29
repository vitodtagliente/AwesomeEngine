/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/application/application_module.h>

namespace net
{
	class Module: public ApplicationModule
	{
	public:
		Module() = default;

		virtual void startup() override;
		virtual void update(double deltaTime) override;
		virtual void shutdown() override;
	};
}