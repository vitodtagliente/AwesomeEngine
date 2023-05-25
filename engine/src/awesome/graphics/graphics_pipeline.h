/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>

#include "renderer.h"

class GraphicsPipeline
{
public:
	friend class GraphicsModule;

	struct Metrics
	{
		int drawCalls{ 0 };
	};

	GraphicsPipeline();

	static GraphicsPipeline* const instance() { return s_instance; }

	std::unique_ptr<graphics::Renderer> sceneRenderer;
	std::unique_ptr<graphics::Renderer> uiRenderer;

	Metrics stats;

private:
	bool init();
	void uninit();

	void preRendering();
	void render();
	void postRendering();

	static inline GraphicsPipeline* s_instance{ nullptr };
};