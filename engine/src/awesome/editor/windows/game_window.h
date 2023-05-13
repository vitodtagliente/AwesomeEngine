/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

class GameWindow : public Window
{
public:
	virtual char* const getTitle() const override;
	virtual void render() override;
};