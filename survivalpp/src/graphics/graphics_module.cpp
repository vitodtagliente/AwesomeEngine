#include "graphics_module.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_ttf.h>

#include "components/systems/sprite_system.h"
#include "core/logger.h"
#include "ecs/ecs.h"
#include "engine/canvas.h"
#include "math/algorithm.h"

#include "renderer.h"
#include "texture_library.h"

extern SDL_Renderer* sdl_renderer{ nullptr };

using namespace graphics;

bool GraphicsModule::startup(SystemRegistry& render_systems, SystemRegistry& update_systems)
{
	SDL_Window* const handler = reinterpret_cast<SDL_Window*>(Canvas::instance().getHandler());
	if (handler == nullptr) return false;

	sdl_renderer = SDL_CreateRenderer(handler, nullptr, SDL_RENDERER_ACCELERATED);
	if (sdl_renderer == nullptr)
	{
		SDL_Log("SDL_CreateRenderer failed (%s)", SDL_GetError());
		return false;
	}

	SDL_SetRenderVSync(sdl_renderer, 0);

	if (TTF_Init() != 0)
	{
		SDL_Log("TTF_Init failed (%s)", TTF_GetError());
		return false;
	}

	render_systems.push_back<SpriteSystem>();

	return true;
}

void GraphicsModule::shutdown()
{
	graphics::TextureLibrary::instance().clear();
	TTF_Quit();
	SDL_DestroyRenderer(sdl_renderer);
}

graphics::Texture* arthur;

void GraphicsModule::preRendering()
{
	Renderer& renderer = Renderer::instance();
	renderer.submitClear();
	
	Canvas& canvas = Canvas::instance();
	renderer.submitSetViewport(canvas.getWidth(), canvas.getHeight());
	renderer.color = graphics::Color::Black;
}

void GraphicsModule::render()
{
	
}

void GraphicsModule::postRendering()
{
	Renderer& renderer = Renderer::instance();
	renderer.flush();
}