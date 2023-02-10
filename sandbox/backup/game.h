/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/application/application_module.h>

class Game : public ApplicationModule
{
public:
	void startup() override;
	void shutdown() override;
};