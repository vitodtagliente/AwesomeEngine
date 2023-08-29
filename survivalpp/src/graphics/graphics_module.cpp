#include "graphics_module.h"

#include <vdtgraphics/context.h>

#include "components/systems/sprite_system.h"
#include "core/logger.h"
#include "ecs/ecs.h"
#include "engine/canvas.h"
#include "math/algorithm.h"

#include "renderer.h"
#include "texture_library.h"

using namespace graphics;

extern graphics::Context* graphics_context{ nullptr };

bool GraphicsModule::startup(SystemRegistry& render_systems, SystemRegistry& update_systems)
{
	graphics_context = new graphics::Context();
	if (graphics_context->initialize() != graphics::Context::State::Initialized)
	{
		return false;
	}

	Renderer::instance().init(graphics_context);

	render_systems.push_back<SpriteSystem>();
	return true;
}

void GraphicsModule::shutdown()
{
	graphics::TextureLibrary::instance().clear();
}

graphics::Texture* arthur;

void GraphicsModule::preRendering()
{
	Renderer& renderer = Renderer::instance();
	renderer.begin();
	
	Canvas& canvas = Canvas::instance();
	graphics_context->viewport(canvas.getWidth(), canvas.getHeight());

	const float aspectRatio = 1.0f;
	renderer.sprites->setProjectionMatrix(Camera::ortho(-10.f, 100.f, static_cast<float>(canvas.getWidth() / 32), static_cast<float>(canvas.getHeight() / 32), aspectRatio)); // 32 pixel per unit
	renderer.sprites->setViewMatrix(math::mat4::identity);	
	renderer.primitives->setProjectionMatrix(Camera::ortho(-10.f, 100.f, static_cast<float>(canvas.getWidth() / 32), static_cast<float>(canvas.getHeight() / 32), aspectRatio)); // 32 pixel per unit
	renderer.primitives->setViewMatrix(math::mat4::identity);
	renderer.text->setProjectionMatrix(math::mat4::orthographic(0.f, static_cast<float>(canvas.getWidth()), static_cast<float>(canvas.getWidth()), 0.f, -10.f, 100.f));
	renderer.text->setViewMatrix(math::mat4::identity);
}

void GraphicsModule::render()
{
	
}

void GraphicsModule::postRendering()
{
	Renderer& renderer = Renderer::instance();
	renderer.flush();
}