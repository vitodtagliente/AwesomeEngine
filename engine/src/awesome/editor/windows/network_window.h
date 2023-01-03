/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <awesome/editor/window.h>

#include "network_window_generated.h"

CLASS(Type = Window)
class NetworkWindow : public Window
{
public:
	NetworkWindow() = default;
	virtual ~NetworkWindow() = default;

	std::string getTitle() const override;
	void render() override;

	GENERATED_BODY()
};