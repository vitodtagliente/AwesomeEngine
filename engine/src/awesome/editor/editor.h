/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>
#include <memory>
#include <queue>
#include <vector>

#include <awesome/engine/engine_module.h>

#include "window.h"

class Editor : public EngineModule
{
public:
	Editor();

	virtual bool startup() override;
	virtual void shutdown() override;
	virtual void preRendering() override;
	virtual void render() override;
	virtual void postRendering() override;
	virtual void update(double deltaTime) override;

	static Editor* const instance() { return s_instance; }

	template <typename T = Window>
	void registerWindow()
	{
		m_windows.push_back(std::make_unique<T>());
	}

	const std::vector<std::unique_ptr<Window>>& getWindows() const { return m_windows; }

private:
	void registerWindows();

	std::vector<std::unique_ptr<Window>> m_windows;
	
	static Editor* s_instance;
};