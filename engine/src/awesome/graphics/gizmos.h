/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include "gizmos_batch.h"

#include <awesome/core/singleton.h>
#include "gizmos_batch.h"
#include <vdtmath/vector3.h>
#include "color.h"

class Gizmos : public Singleton<Gizmos>
{
public:

	Gizmos();

	void line(const math::vec3& a, const math::vec3& b, const Color& color);
	void rect(const math::vec3& position, float width, float height, const Color& color);
	void circle(const math::vec3& position, float radius, const Color& color);
	void clear();

	std::vector<Command*> commands() const;

private:

	GizmosBatch m_batch;

};