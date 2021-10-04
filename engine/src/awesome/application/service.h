/// Copyright (c) Vito Domenico Tagliente

#pragma once

class Service
{
public:

	Service() = default;
	virtual ~Service() = default;

	virtual bool startup() = 0;
	virtual void shutdown() = 0;
};