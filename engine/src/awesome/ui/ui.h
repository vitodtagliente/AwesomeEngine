/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/application/application_module.h>

#include "ui_element.h"

class UI : public ApplicationModule
{
public:
	struct Performances
	{
		int drawCalls{ 0 };
	};

	UI();

	virtual void startup() override;
	virtual void shutdown() override;
	virtual void preRendering() override;
	virtual void render() override;
	virtual void postRendering() override;
	virtual void update(double deltaTime) override;

	static UI* const instance() { return s_instance; }

	Performances performances;

private:
	static UI* s_instance;
};