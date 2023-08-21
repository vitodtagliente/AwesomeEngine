#include "render_target.h"

#include <SDL3/SDL.h>

namespace graphics
{
	RenderTarget::RenderTarget(const int width, const int height, const Color& color)
		: m_width(width)
		, m_height(height)
		, color(color)
	{
		
	}

	RenderTarget::~RenderTarget()
	{
		free();
	}

	void RenderTarget::resize(const int width, const int height)
	{
		if (width == m_width && height == m_height) return;

		m_width = width;
		m_height = height;

		
	}

	void RenderTarget::free()
	{
		
	}
}