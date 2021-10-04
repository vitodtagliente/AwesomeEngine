#include "fps.h"

FPS::FPS()
	: m_clock(std::chrono::steady_clock::now())
	, m_counter()
	, m_time(std::chrono::duration<float>(0.0f))
	, m_fps()
{

}

FPS::~FPS()
{

}

void FPS::update()
{
	static const std::chrono::duration<float> interval(1.0f);


	const std::chrono::steady_clock::time_point& now = std::chrono::steady_clock::now();

	const std::chrono::duration<float> delta_time =
		std::chrono::duration_cast<std::chrono::duration<float>>(now - m_clock);

	++m_counter;
	m_time += delta_time;
	m_clock = now;

	if (m_time >= interval)
	{
		m_fps = m_counter;
		// reset frame count
		m_counter = 0;
		// reset frame time
		m_time = std::chrono::duration<float>(0.0f);
	}
}