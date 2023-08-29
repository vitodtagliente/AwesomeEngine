/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

#include <awesome/math/vector3.h>
#include <awesome/math/matrix4.h>

#include "color.h"
#include "common.h"
#include "texture_rect.h"

namespace graphics
{
	class Context;
	class Font;
	class PrimitiveBatch;
	class SpriteBatch;
	class TextBatch;
	class Texture;

	class Renderer
	{
	public:
		struct Stats
		{
			std::size_t draw_calls{ 0 };
			std::size_t draw_entities{ 0 };
		};

		Renderer(Context* const context);

		void setProjectionMatrix(const math::matrix4& m);
		void setViewMatrix(const math::matrix4& m);
		const math::matrix4& getProjectionMatrix() const { return m_projectionMatrix; }
		const math::matrix4& getViewMatrix() const { return m_viewMatrix; }
		const math::matrix4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

		void begin(int width, int height, const Color& color = Color::Black);
		void flush();

		void drawCircle(ShapeRenderStyle style, const math::vec3& position, float radius, const Color& color);
		void drawLine(const math::vec3& point1, const Color& color1, const math::vec3& point2, const Color& color2);
		void drawShape(ShapeRenderStyle style, const std::vector<Vertex>& vertices);
		void drawRect(ShapeRenderStyle style, const math::vec3& position, float width, float height, const Color& color);

		void drawTexture(Texture* const texture, const math::mat4& matrix, const TextureRect& rect = {}, const Color& color = Color::White);
		void drawTexture(Texture* const texture, const math::vec3& position, const TextureRect& rect = {}, const Color& color = Color::White);
		void drawTexture(Texture* const texture, const math::vec3& position, float rotation, const TextureRect& rect = {}, const Color& color = Color::White);
		void drawTexture(Texture* const texture, const math::vec3& position, const math::vec3& scale, const TextureRect& rect = {}, const Color& color = Color::White);
		void drawTexture(Texture* const texture, const math::vec3& position, float rotation, const math::vec3& scale, const TextureRect& rect = {}, const Color& color = Color::White);

		void drawText(Font* const font, const std::string& text, const math::vec3& position, std::size_t size = 16, const Color& color = Color::White);

		int pixelsPerUnit{ 32 };
		Stats stats;

	private:
		Context* m_context{ nullptr };
		std::unique_ptr<PrimitiveBatch> m_primitives;
		std::unique_ptr<SpriteBatch> m_sprites;
		std::unique_ptr<TextBatch> m_text;

		// matrices
		math::mat4 m_projectionMatrix{ math::mat4::identity };
		math::mat4 m_viewMatrix{ math::mat4::identity };
		math::mat4 m_viewProjectionMatrix{ math::mat4::identity };
	};
}