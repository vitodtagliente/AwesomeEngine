/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

#include "settings_window_generated.h"

CLASS(Type = Window)
class SettingsWindow : public Window
{
public:
	SettingsWindow() = default;

	virtual std::string getTitle() const override;
	virtual void render() override;

	GENERATED_BODY()
};