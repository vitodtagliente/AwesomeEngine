#pragma once

#include <chrono>

namespace awesome
{
	class FPS
	{
	public:

		FPS();
		~FPS();

		void update();
		inline unsigned int value() const { return m_fps; }

	private:

		// last clock tick
		std::chrono::steady_clock::time_point m_clock;
		// frames counter
		unsigned int m_counter;
		// frame time
		std::chrono::duration<float> m_time;
		// current fps
		unsigned int m_fps;
	};
}