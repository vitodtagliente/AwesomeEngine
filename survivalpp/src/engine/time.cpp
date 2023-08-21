#include "time.h"

Time::Time()
	: m_clock1()
	, m_clock2()
	, m_time(0.0)
	, m_deltaTime(0.0)
{
	m_clock1 = m_clock2 = std::chrono::high_resolution_clock::now();
}

void Time::tick()
{
	m_clock1 = m_clock2;
	m_clock2 = std::chrono::high_resolution_clock::now();

	// m_time to be calculated
	m_deltaTime = std::chrono::duration<double>(m_clock2 - m_clock1).count();
	m_time = +m_deltaTime;
}