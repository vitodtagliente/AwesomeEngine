/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/application/application.h>

namespace net
{
	class Module: public Application::Module
	{
	public:
		Module() = default;

		virtual void startup() override;
		virtual void update(double deltaTime) override;
		virtual void shutdown() override;
	};
}