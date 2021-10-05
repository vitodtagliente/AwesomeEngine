/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include "color.h"
#include <awesome/core/singleton.h>

class Command;
class Context;

class Renderer : public Singleton<Renderer>
{
public:

	Renderer(Context& context);

	void begin();
	void flush();
	void clear();

	Color backgroundColor;

private:

	Context& m_context;
	std::vector<Command*> m_commands;

};