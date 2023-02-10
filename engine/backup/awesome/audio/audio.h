/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/application/application_module.h>

class Audio : public ApplicationModule
{
public:
	Audio();

	virtual void startup() override;
	virtual void shutdown() override;

	static Audio* const instance() { return s_instance; }

private:
	static Audio* s_instance;
};