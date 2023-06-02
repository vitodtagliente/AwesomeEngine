#include "graphics_pipeline.h"

#include <cassert>

#include <awesome/core/logger.h>
#include <awesome/components/camera_component.h>
#include <awesome/engine/canvas.h>
#include <awesome/engine/engine_settings.h>
#include <awesome/scene/scene_graph.h>

#include "graphics_context.h"

extern graphics::Context* graphics_context;

const std::string GraphicsPipeline::RenderStage::Name::Scene = "scene";
const std::string GraphicsPipeline::RenderStage::Name::UI = "ui";
const std::string GraphicsPipeline::RenderStage::Name::Wireframes = "wireframes";

GraphicsPipeline::RenderStage::RenderStage(const std::string& name)
	: name(name)
{

}

bool GraphicsPipeline::RenderStage::init()
{
	renderer = std::make_unique<graphics::Renderer>();
	if (!renderer->init(graphics_context))
	{
		ERR_LOG(THIS_FUNC, "Unable to initialize the " + name + " renderer");
		return false;
	}
	renderTarget = std::make_unique<graphics::RenderTarget>(1080, 720);
	// renderer->setRenderTarget(renderTarget.get());
	return true;
}

GraphicsPipeline::GraphicsPipeline()
	: m_mode(EngineSettings::instance().mode)
{
	assert(s_instance == nullptr);
	s_instance = this;
}

graphics::Renderer* const GraphicsPipeline::renderer(const std::string& name)
{
	RenderStage* const render_stage = stage(name);
	if (render_stage)
	{
		return render_stage->renderer.get();
	}
	return nullptr;
}

GraphicsPipeline::RenderStage* const GraphicsPipeline::stage(const std::string& name)
{
	const auto& it = std::find_if(
		m_stages.begin(),
		m_stages.end(),
		[&name](const RenderStage& stage) -> bool
		{
			return stage.name == name;
		}
	);

	if (it != m_stages.end())
	{
		RenderStage& stage = *it;
		return &stage;
	}
	return nullptr;
}

bool GraphicsPipeline::init()
{
	m_stages.push_back(RenderStage(RenderStage::Name::Scene));
	m_stages.push_back(RenderStage(RenderStage::Name::UI));
	m_stages.push_back(RenderStage(RenderStage::Name::Wireframes));

	for (auto& stage : m_stages)
	{
		if (!stage.init()) return false;
	}
	return true;
}

void GraphicsPipeline::uninit()
{
}

void GraphicsPipeline::preRendering()
{
	CameraComponent* const camera = CameraComponent::main();
	if (!m_stages.empty())
	{
		m_stages.front().renderer->submitClear(camera ? camera->color : graphics::Color::Black);
		m_stages.front().renderer->submitSetViewport(viewport.width, viewport.height);
	}
}

void GraphicsPipeline::render()
{
	Canvas& canvas = Canvas::instance();
	viewport.width = canvas.getWidth();
	viewport.height = canvas.getHeight();

	SceneGraph::instance().render(*renderer(RenderStage::Name::Scene));
}

void GraphicsPipeline::postRendering()
{
	stats.drawCalls = 0;
	for (auto& stage : m_stages)
	{
		graphics::Renderer& stage_renderer = *stage.renderer;
		stage_renderer.draw();
		stats.drawCalls += stage.renderer->stats.drawCalls;
	}
}

