#pragma once

namespace awesome
{
	class Game
	{
	public:

		friend class Engine;

		// game state
		enum class State
		{
			Unknown,
			Running,
			Ended
		};

		Game();
		virtual ~Game() = default;

		inline State getState() const { return m_state; }

	protected:

		virtual void init();
		virtual void update();
		virtual void uninit();
		virtual void end();

		// game state
		State m_state;
	};
}