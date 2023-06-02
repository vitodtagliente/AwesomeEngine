#include "graphics_module.h"

#include <awesome/core/logger.h>

#include "graphics_context.h"
#include "graphics_pipeline.h"
#include "texture_library.h"

extern graphics::Context* graphics_context{ nullptr };
GraphicsPipeline* graphics_pipeline{ nullptr };

bool GraphicsModule::startup()
{
	graphics_context = new graphics::Context();
	if (graphics_context->initialize() != graphics::Context::State::Initialized)
	{
		return false;
	}

	graphics_pipeline = new GraphicsPipeline();
	if(!graphics_pipeline->init())
	{
		ERR_LOG(THIS_FUNC, "Unable to initialize the graphics pipeline");
		return false;
	}
	return true;
}

void GraphicsModule::shutdown()
{
	graphics_pipeline->uninit();
	delete graphics_pipeline;
}

void GraphicsModule::preRendering()
{
	// must be executed in the main thread
	TextureLibrary::instance().flush();

	graphics_pipeline->preRendering();
}

void GraphicsModule::render()
{
	graphics_pipeline->render();
}

void GraphicsModule::postRendering()
{
	graphics_pipeline->postRendering();
}