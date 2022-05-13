/// Copyright (c) Vito Domenico Tagliente
#pragma once

class Timer
{
public:
	Timer(double time);

	inline double getRemainingTime() const { return m_timer; }
	inline bool isExpired() const { return m_timer <= 0.f; }
	inline bool isTicking() const { return m_canTick; }

	void tick(double deltaTime);
	
	void expire();
	void pause();
	void reset();
	void reset(double time);
	void resume();
	void stop();

	void configure(double time);

private:
	double m_time;
	double m_timer;
	bool m_canTick;
};