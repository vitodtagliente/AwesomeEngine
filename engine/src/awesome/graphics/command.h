/// Copyright (c) Vito Domenico Tagliente
#pragma once

class Context;

class Command
{
public:

	virtual void execute(Context& context) = 0;
};