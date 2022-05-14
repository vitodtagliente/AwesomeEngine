#include "renderer.h"

#include "command.h"
#include "context.h"
#include "texture.h"

namespace graphics
{
	Renderer::Renderer()
		: backgroundColor(Color::Black)
		, m_context(Context::instance())
		, m_gizmos()
		, m_spriteBatch()
		, m_commands()
		, m_stats()
	{

	}

	void Renderer::begin()
	{
		m_context.clear(backgroundColor);
		m_context.viewProjectionMatrix = m_context.projection * m_context.view;
		m_context.drawCalls = 0;
		m_stats = {};
	}

	void Renderer::flush()
	{
		for (auto it = m_commands.begin(); it != m_commands.end(); ++it)
		{
			Command* const command = *it;
			command->execute(m_context);
		}

		m_spriteBatch.flush(&m_context);
		m_gizmos.getBatch().flush(&m_context);
		m_stats.drawCalls = m_context.drawCalls;
	}

	void Renderer::clear()
	{
		m_commands.clear();
		m_stats = {};
	}

	void Renderer::setProjection(const math::mat4& matrix)
	{
		m_context.projection = matrix;
	}

	void Renderer::setView(const math::mat4& matrix)
	{
		m_context.view = matrix;
	}

	const math::mat4& Renderer::getProjection() const
	{
		return m_context.projection;
	}

	const math::mat4& Renderer::getView() const
	{
		return m_context.view;
	}

	const math::mat4& Renderer::getViewProjectionMatrix() const
	{
		return m_context.viewProjectionMatrix;
	}

	void Renderer::drawSprite(Texture* const texture, const math::mat4& matrix, const TextureRect& rect, const Color& color)
	{
		m_spriteBatch.batch(texture, matrix, rect, color);
	}

	Renderer::Stats::Stats()
		: drawCalls(0)
	{
	}
}
