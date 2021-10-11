/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>
#include <vector>
#include <vdtmath/vector3.h>

class PathNavigator
{
public:
	PathNavigator();

	bool isCompleted() const;
	bool isValid() const;
	void follow(class Path* const path);
	bool next(const math::vec3& position, math::vec3& nextPosition);

private:
	class Path* m_path;
	int m_stepIndex;
	float m_marginRadius;
};