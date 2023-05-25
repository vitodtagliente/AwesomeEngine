#include "graphics_pipeline.h"

#include <cassert>

#include <awesome/core/logger.h>
#include <awesome/components/camera_component.h>
#include <awesome/engine/canvas.h>
#include <awesome/scene/scene_graph.h>

#include "graphics_context.h"

extern graphics::Context* graphics_context;

GraphicsPipeline::GraphicsPipeline()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

bool GraphicsPipeline::init()
{
	sceneRenderer = std::make_unique<graphics::Renderer>();
	if (!sceneRenderer->init(graphics_context))
	{
		ERR_LOG(THIS_FUNC, "Unable to initialize the scene renderer");
		return false;
	}

	uiRenderer = std::make_unique<graphics::Renderer>();
	if (!uiRenderer->init(graphics_context))
	{
		ERR_LOG(THIS_FUNC, "Unable to initialize the UI renderer");
		return false;
	}

	return true;
}

void GraphicsPipeline::uninit()
{
}

void GraphicsPipeline::preRendering()
{
	const auto& canvas = Canvas::instance();
	sceneRenderer->submitSetViewport(canvas.getWidth(), canvas.getHeight());

	CameraComponent* const camera = CameraComponent::main();
	sceneRenderer->submitClear(camera ? camera->color : graphics::Color::Black);
}

void GraphicsPipeline::render()
{
	SceneGraph::instance().render(*sceneRenderer);
}

void GraphicsPipeline::postRendering()
{
	sceneRenderer->draw();
	uiRenderer->draw();
	stats.drawCalls = sceneRenderer->stats.drawCalls + uiRenderer->stats.drawCalls;
}

