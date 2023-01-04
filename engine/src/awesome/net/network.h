/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>

#include <awesome/application/application_module.h>

class Network : public ApplicationModule
{
public:
	Network();

	virtual void startup() override;
	virtual void update(double deltaTime) override;
	virtual void shutdown() override;

	static Network* const instance() { return s_instance; }

private:
	static Network* s_instance;
};
