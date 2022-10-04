/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/application/application.h>
#include <awesome/editor/window.h>

#include "settings_window_generated.h"

CLASS(Category = Window)
class SettingsWindow : public Window
{
public:
	SettingsWindow();

	std::string getTitle() const override { return "Settings"; }
	void render() override;

	GENERATED_BODY()

private:
	ApplicationSettings m_settings;
};