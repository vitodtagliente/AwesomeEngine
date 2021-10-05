/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include "color.h"
#include <awesome/core/singleton.h>
#include "gizmos.h"

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

	inline Gizmos& getGizmos() { return m_gizmos; }

private:

	Context& m_context;
	Gizmos m_gizmos;
	std::vector<Command*> m_commands;

};