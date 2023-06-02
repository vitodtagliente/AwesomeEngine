/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <vector>
#include <string>

#include <awesome/engine/engine_settings.h>

#include "renderer.h"
#include "render_target.h"

class GraphicsPipeline
{
public:
	friend class GraphicsModule;

	struct Metrics
	{
		int drawCalls{ 0 };
	};

	struct RenderStage final
	{
		struct Name final
		{
			static const std::string Scene;
			static const std::string UI;
			static const std::string Wireframes;
		};

		RenderStage(const std::string& name);

		bool init();

		std::unique_ptr<graphics::Renderer> renderer;
		std::unique_ptr<graphics::RenderTarget> renderTarget;
		std::string name;
	};

	struct Viewport final
	{
		int width{ 1080 };
		int height{ 720 };
	};

	GraphicsPipeline();

	static GraphicsPipeline* const instance() { return s_instance; }

	graphics::Renderer* const renderer(const std::string& name);
	RenderStage* const stage(const std::string& name);

	Metrics stats;
	Viewport viewport;

private:
	bool init();
	void uninit();

	void preRendering();
	void render();
	void postRendering();

	EngineMode m_mode;
	std::vector<RenderStage> m_stages;

	static inline GraphicsPipeline* s_instance{ nullptr };
};