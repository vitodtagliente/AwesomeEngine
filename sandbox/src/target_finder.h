/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <vdtmath/vector3.h>

class Entity;
class World;

class TargetFinder
{
public:
	
	enum class Mode
	{
		Closer,
		FIFO
	};

	TargetFinder(float radius, Mode mode = Mode::Closer);

	Entity* const getTarget() const;
	bool hasTarget() const;
	inline float getRadius() const { return m_radius; }
	void check(World& world, const math::vec3& position);

private:
	Entity* const findTheClosest(World& world, const math::vec3& position);

	Mode m_mode;
	Entity* m_target;
	float m_radius;
};