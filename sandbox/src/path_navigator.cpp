#include "path_navigator.h"

#include "path.h"

PathNavigator::PathNavigator()
	: m_path()
	, m_stepIndex(0)
	, m_marginRadius(.25f)
{
}

bool PathNavigator::isCompleted() const
{
	if (m_path != nullptr)
	{
		return m_stepIndex >= m_path->steps.size();
	}
	return false;
}

bool PathNavigator::isValid() const
{
	return m_path != nullptr;
}

void PathNavigator::follow(Path* const path)
{
	m_path = path;
	m_stepIndex = 0;
}

bool PathNavigator::next(const math::vec3& position, math::vec3& nextPosition)
{
	if (!isValid() || isCompleted())
	{
		return false;
	}

	const math::vec3& step = m_path->steps[m_stepIndex];
	if (position.distance(step) < m_marginRadius)
	{
		++m_stepIndex;
	}

	if (isCompleted()) return false;
	nextPosition = m_path->steps[m_stepIndex];
	return true;
}