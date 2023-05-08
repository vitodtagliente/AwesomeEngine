#include "graphics.h"

#include <assert.h>

#include <awesome/components/camera_component.h>
#include <awesome/engine/canvas.h>
#include <awesome/scene/scene_graph.h>

#include "context.h"
#include "renderer.h"

Graphics* Graphics::s_instance{ nullptr };

Graphics::Graphics()
	: EngineModule()
{
	assert(s_instance == nullptr);
	s_instance = this;
}

bool Graphics::startup()
{
	m_context = std::make_unique<graphics::Context>();
	if (m_context->initialize() != graphics::Context::State::Initialized)
	{
		return false;
	}

	renderer = std::make_unique<graphics::Renderer>();
	if (!renderer->init(m_context.get()))
	{
		return false;
	}
	return true;
}

void Graphics::shutdown()
{
}

void Graphics::preRendering()
{
	const auto& canvas = Canvas::instance();
	renderer->setViewport(canvas.getWidth(), canvas.getHeight());

	CameraComponent* const camera = CameraComponent::main();
	renderer->clear(camera ? camera->color : graphics::Color::Black);
}

void Graphics::render()
{
	SceneGraph::instance().root().render(*renderer);
}

void Graphics::postRendering()
{	
	renderer->flush();
	performances.drawCalls = renderer->stats.drawCalls;
}