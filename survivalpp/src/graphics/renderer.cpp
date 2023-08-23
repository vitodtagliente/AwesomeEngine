#include "renderer.h"

#include <SDL3/SDL.h>

extern SDL_Renderer* sdl_renderer;

namespace graphics
{
	void Renderer::submitClear()
	{
		SDL_SetRenderDrawColor(sdl_renderer, static_cast<Uint8>(color.red * 255), static_cast<Uint8>(color.green * 255), static_cast<Uint8>(color.blue * 255), static_cast<Uint8>(color.alpha * 255));
		SDL_RenderClear(sdl_renderer);
	}

	void Renderer::submitSetViewport(const int width, const int height)
	{
		m_viewport = math::vec2(static_cast<float>(width) / 2, static_cast<float>(height) / 2);
	}

	void Renderer::submitDrawCircle(const ShapeRenderStyle style, const math::vec2& position, float radius, const Color& color)
	{
		const math::vec2 size(radius / 2 * pixelsPerUnit, radius / 2 * pixelsPerUnit);
		SDL_FRect rect = { m_viewport.x + position.x * pixelsPerUnit - size.x, m_viewport.y - position.y * pixelsPerUnit - size.y, size.x * 2, size.y * 2 };
		SDL_SetRenderDrawColor(sdl_renderer, static_cast<Uint8>(color.red * 255), static_cast<Uint8>(color.green * 255), static_cast<Uint8>(color.blue * 255), static_cast<Uint8>(color.alpha * 255));

		switch (style)
		{
		case ShapeRenderStyle::stroke: SDL_RenderRect(sdl_renderer, &rect); break;
		case ShapeRenderStyle::fill:
		default:
			SDL_RenderFillRect(sdl_renderer, &rect); break;
		}
	}

	void Renderer::submitDrawLine(const math::vec2& point1, const math::vec2& point2, const Color& color)
	{
		SDL_SetRenderDrawColor(sdl_renderer, static_cast<Uint8>(color.red * 255), static_cast<Uint8>(color.green * 255), static_cast<Uint8>(color.blue * 255), static_cast<Uint8>(color.alpha * 255));
		SDL_RenderLine(sdl_renderer, point1.x * pixelsPerUnit, -point1.y * pixelsPerUnit, point2.x * pixelsPerUnit, -point2.y * pixelsPerUnit);
	}

	void Renderer::submitDrawRect(const ShapeRenderStyle style, const math::vec2& position, float width, float height, const Color& color)
	{
		const math::vec2 size(width / 2 * pixelsPerUnit, height / 2 * pixelsPerUnit);
		SDL_FRect rect = { m_viewport.x + position.x * pixelsPerUnit - size.x, m_viewport.y - position.y * pixelsPerUnit - size.y, size.x * 2, size.y * 2 };
		SDL_SetRenderDrawColor(sdl_renderer, static_cast<Uint8>(color.red * 255), static_cast<Uint8>(color.green * 255), static_cast<Uint8>(color.blue * 255), static_cast<Uint8>(color.alpha * 255));
		
		switch (style)
		{
		case ShapeRenderStyle::stroke: SDL_RenderRect(sdl_renderer, &rect); break;
		case ShapeRenderStyle::fill:
		default:
			SDL_RenderFillRect(sdl_renderer, &rect); break;
		}
	}

	void Renderer::submitDrawTexture(Texture* const texture, const math::vec2& position, const float angle, const math::vec2& scale, const TextureRect& rect, const TextureFlipMode flip, const Color& color)
	{
		SpriteRenderData& data = m_next_sprites.emplace_back();

		data.texture = texture;

		const math::vec2 full_size(pixelsPerUnit * scale.x, pixelsPerUnit * scale.y);
		const math::vec2 size = full_size / 2.f;
		data.clip = { rect.x * texture->width(), rect.y * texture->height(), rect.width * texture->width(), rect.height * texture->height() };
		data.dest = { m_viewport.x + position.x * pixelsPerUnit - size.x, m_viewport.y - position.y * pixelsPerUnit - size.y, full_size.x, full_size.y };

		switch (flip)
		{
		case TextureFlipMode::Horizontal: data.flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL; break;
		case TextureFlipMode::Vertical: data.flip = SDL_RendererFlip::SDL_FLIP_VERTICAL; break;
		case TextureFlipMode::Both: data.flip = static_cast<SDL_RendererFlip>(SDL_RendererFlip::SDL_FLIP_HORIZONTAL | SDL_RendererFlip::SDL_FLIP_VERTICAL); break;
		case TextureFlipMode::None:
		default: 
			data.flip = SDL_RendererFlip::SDL_FLIP_NONE; break;
		}		
	}

	void Renderer::flush()
	{
		for (const SpriteRenderData& data : m_sprites)
		{
			SDL_RenderTextureRotated(sdl_renderer, data.texture->data(), &data.clip, &data.dest, data.angle, nullptr, static_cast<SDL_RendererFlip>(data.flip));
		}

		SDL_RenderPresent(sdl_renderer);
	}

	void Renderer::next_frame()
	{
		m_sprites.clear();
		for (auto data : m_next_sprites)
		{
			m_sprites.push_back(std::move(data));
		}
		m_next_sprites.clear();
	}

	math::vec2 Renderer::screenToWorld(const math::vec2& position)
	{
		return math::vec2((position.x - m_viewport.x) / pixelsPerUnit, (m_viewport.y - position.y) / pixelsPerUnit);
	}
}