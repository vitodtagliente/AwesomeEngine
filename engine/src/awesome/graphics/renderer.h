/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include <vdtmath/matrix4.h>

#include <awesome/core/singleton.h>

#include "color.h"
#include "gizmos.h"
#include "sprite_batch.h"
#include "texture_rect.h"

namespace graphics
{
	class Command;
	class Context;
	class Texture;

	class Renderer : public Singleton<Renderer>
	{
	public:

		struct Stats
		{
			Stats();

			int drawCalls;
		};

		Renderer();

		void begin();
		void flush();
		void clear();

		void setProjection(const math::mat4& matrix);
		void setView(const math::mat4& matrix);
		const math::mat4& getProjection() const;
		const math::mat4& getView() const;
		const math::mat4& getViewProjectionMatrix() const;

		void drawSprite(Texture* const texture, const math::mat4& matrix, const TextureRect& rect = {}, const Color& color = Color::White);

		Color backgroundColor;

		inline Gizmos& getGizmos() { return m_gizmos; }
		inline const Stats& getStats() const { return m_stats; }

	private:
		Context& m_context;
		Gizmos m_gizmos;
		SpriteBatch m_spriteBatch;
		std::vector<Command*> m_commands;
		Stats m_stats;

	};
}