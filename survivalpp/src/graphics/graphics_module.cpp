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
extern graphics::Renderer* g_renderer{ nullptr };

using namespace graphics;

bool GraphicsModule::startup(SystemRegistry& render_systems, SystemRegistry& update_systems)
{
	SDL_Window* const handler = reinterpret_cast<SDL_Window*>(Canvas::instance().getHandler());
	if (handler == nullptr) return false;

	sdl_renderer = SDL_CreateRenderer(handler, nullptr, 0);
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

	g_renderer = &graphics::Renderer::instance();

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
	graphics::Color& clear_color = g_renderer->color;
	SDL_SetRenderDrawColor(sdl_renderer, static_cast<Uint8>(clear_color.red * 255), static_cast<Uint8>(clear_color.green * 255), static_cast<Uint8>(clear_color.blue * 255), static_cast<Uint8>(clear_color.alpha * 255));
	SDL_RenderClear(sdl_renderer);
	
	Canvas& canvas = Canvas::instance();
	g_renderer->submitSetViewport(canvas.getWidth(), canvas.getHeight());
	g_renderer->color = graphics::Color::Black;

	arthur = graphics::TextureLibrary::instance().find("../data/arthur.png");
}

void GraphicsModule::render()
{
	// g_renderer->submitDrawRect(ShapeRenderStyle::fill, math::vec2(), 2.f, 2.f, graphics::Color::Cyan);
	// g_renderer->submitDrawRect(ShapeRenderStyle::stroke, math::vec2(10.f, 10.f), 1.f, 1.f, graphics::Color::Red);
	// g_renderer->submitDrawTexture(arthur, math::vec2(0.f, 0.f), 0.f, math::vec2(2.f, 2.f), graphics::TextureRect(0.f, 0.f, 1.f / 8, 1.f / 6), TextureFlipMode::Both);
	// g_renderer->submitDrawTexture(arthur);
}

void GraphicsModule::postRendering()
{
	SDL_RenderPresent(sdl_renderer);
}