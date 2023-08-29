#include "renderer.h"

graphics::Renderer::Renderer(Context* const context)
{
	m_context = context;
	m_primitives = std::make_unique<PrimitiveBatch>(context);
	m_sprites = std::make_unique<SpriteBatch>(context);
	m_text = std::make_unique<TextBatch>(context);
}

void graphics::Renderer::setProjectionMatrix(const math::matrix4& m)
{
	m_projectionMatrix = m;
	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

void graphics::Renderer::setViewMatrix(const math::matrix4& m)
{
	m_viewMatrix = m;
	m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
}

void graphics::Renderer::begin(const int width, const int height, const Color& color)
{
	m_context->clear(color);
	m_context->viewport(width, height);

	const float width_f = static_cast<float>(width);
	const float height_f = static_cast<float>(height);

	const float aspectRatio = 1.0f;
	m_sprites->setProjectionMatrix(m_projectionMatrix);
	m_sprites->setViewMatrix(m_viewMatrix);
	m_primitives->setProjectionMatrix(m_projectionMatrix);
	m_primitives->setViewMatrix(m_viewMatrix);
	m_text->setProjectionMatrix(math::mat4::orthographic(0.f, width_f, height_f, 0.f, -10.f, 100.f));
	m_text->setViewMatrix(math::mat4::identity);

}

void graphics::Renderer::flush()
{
	m_primitives->flush();
	m_sprites->flush();
	m_text->flush();

	stats.draw_calls = m_primitives->stats().draw_calls
		+ m_sprites->stats().draw_calls
		+ m_text->stats().draw_calls;
	stats.draw_entities = m_primitives->stats().draw_entities
		+ m_sprites->stats().draw_entities
		+ m_text->stats().draw_entities;
}

void graphics::Renderer::drawCircle(ShapeRenderStyle style, const math::vec3& position, float radius, const Color& color)
{
	m_primitives->drawCircle(style, position, radius, color);
}

void graphics::Renderer::drawLine(const math::vec3& point1, const Color& color1, const math::vec3& point2, const Color& color2)
{
	m_primitives->drawLine(point1, color1, point2, color2);
}

void graphics::Renderer::drawShape(ShapeRenderStyle style, const std::vector<Vertex>& vertices)
{
	m_primitives->drawShape(style, vertices);
}

void graphics::Renderer::drawRect(ShapeRenderStyle style, const math::vec3& position, float width, float height, const Color& color)
{
	m_primitives->drawRect(style, position, width, height, color);
}

void graphics::Renderer::drawTexture(Texture* const texture, const math::mat4& matrix, const TextureRect& rect, const Color& color)
{
	m_sprites->draw(texture, matrix, rect, color);
}

void graphics::Renderer::drawTexture(Texture* const texture, const math::vec3& position, const TextureRect& rect, const Color& color)
{
	m_sprites->draw(texture, position, rect, color);
}

void graphics::Renderer::drawTexture(Texture* const texture, const math::vec3& position, float rotation, const TextureRect& rect, const Color& color)
{
	m_sprites->draw(texture, position, rotation, rect, color);
}

void graphics::Renderer::drawTexture(Texture* const texture, const math::vec3& position, const math::vec3& scale, const TextureRect& rect, const Color& color)
{
	m_sprites->draw(texture, position, scale, rect, color);
}

void graphics::Renderer::drawTexture(Texture* const texture, const math::vec3& position, float rotation, const math::vec3& scale, const TextureRect& rect, const Color& color)
{
	m_sprites->draw(texture, position, rotation, scale, rect, color);
}

void graphics::Renderer::drawText(Font* const font, const std::string& text, const math::vec3& position, std::size_t size, const Color& color)
{
	m_text->draw(font, text, position, size, color);
}
