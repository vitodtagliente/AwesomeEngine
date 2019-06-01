#pragma once

#include <vector>

namespace awesome
{
	struct RenderCommand;

	class CommandBuffer
	{
	public:

		CommandBuffer();
		~CommandBuffer();

		void sort();
		void push_back(RenderCommand * const t_command);
		inline const std::vector<RenderCommand*>& getCommands() const { return m_commands; }
		void clear();

	private:
		
		// render commands
		std::vector<RenderCommand*> m_commands;
	};
}