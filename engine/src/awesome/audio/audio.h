/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/application/application.h>

class Audio : public Application::Module
{
public:
	Audio() = default;
	virtual ~Audio() = default;

	virtual void startup() override;
	virtual void shutdown() override;
};