#include "gizmos.h"

#include <vdtmath/algorithm.h>

#include "command.h"

namespace graphics
{
	const float CIRCLE_ACCURACY = 40.0f;

	Gizmos::Gizmos()
		: m_batch()
	{
	}

	void Gizmos::line(const math::vec3& a, const math::vec3& b, const Color& color)
	{
		m_batch.batch(a, color);
		m_batch.batch(b, color);
	}

	void Gizmos::rect(const math::vec3& position, const float width, const float height, const Color& color)
	{
		const float w = width / 2;
		const float h = height / 2;

		m_batch.batch(position + math::vec3(w, h, 0), color);
		m_batch.batch(position + math::vec3(-w, h, 0), color);
		m_batch.batch(position + math::vec3(-w, h, 0), color);
		m_batch.batch(position + math::vec3(-w, -h, 0), color);
		m_batch.batch(position + math::vec3(-w, -h, 0), color);
		m_batch.batch(position + math::vec3(w, -h, 0), color);
		m_batch.batch(position + math::vec3(w, -h, 0), color);
		m_batch.batch(position + math::vec3(w, h, 0), color);
	}

	void Gizmos::circle(const math::vec3& position, const float radius, const Color& color)
	{
		const float accuracy = CIRCLE_ACCURACY * radius;
		const float step = (2 * math::pi) / accuracy;
		float angle = 0.0f;
		for (int i = 0; i < accuracy; ++i)
		{
			line(
				position + math::vec3(radius * std::sin(angle), radius * std::cos(angle), 0),
				position + math::vec3(radius * std::sin(angle + step), radius * std::cos(angle + step), 0),
				color
			);
			angle += step;
		}
	}
}