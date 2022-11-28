/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

#include "game_settings_window_generated.h"

CLASS(Category = Window)
class GameSettingsWindow : public Window
{
public:
	GameSettingsWindow() = default;

	std::string getTitle() const override { return "Game Settings"; }
	void render() override;

	GENERATED_BODY()
};