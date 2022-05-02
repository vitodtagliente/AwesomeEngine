/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <chrono>

class Time
{
public:
	Time();

	// retrieve the time data
	inline double getTime() const { return m_time; }
	inline double getDeltaTime() const { return m_deltaTime; }

	// tick the time
	void tick();

private:
	// high resolution clocks
	std::chrono::high_resolution_clock::time_point m_clock1;
	std::chrono::high_resolution_clock::time_point m_clock2;

	// cache time and delta time
	double m_time;
	double m_deltaTime;
};