/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vector>
#include <vdtmath/vector3.h>

#include <awesome/core/singleton.h>

#include "color.h"
#include "gizmos_batch.h"

namespace graphics
{
	class Command;

	class Gizmos : public Singleton<Gizmos>
	{
	public:
		Gizmos();

		void line(const math::vec3& a, const math::vec3& b, const Color& color);
		void rect(const math::vec3& position, float width, float height, const Color& color);
		void circle(const math::vec3& position, float radius, const Color& color);

		inline GizmosBatch& getBatch() { return m_batch; }

	private:
		GizmosBatch m_batch;

	};
}