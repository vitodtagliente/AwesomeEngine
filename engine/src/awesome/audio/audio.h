/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/application/application_module.h>

class Audio : public ApplicationModule
{
public:
	Audio() = default;
	virtual ~Audio() = default;

	virtual void startup() override;
	virtual void shutdown() override;
};