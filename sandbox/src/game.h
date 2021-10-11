/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/application/application.h>

class Game : public Application::Module
{
public:
	void startup() override;
	void shutdown() override;
};