#pragma once

#include <vector>
#include "render_command.h"

namespace awesome
{
	class CommandBuffer
	{
	public:

		CommandBuffer();
		~CommandBuffer();

		void sort();
		void push_back(const RenderCommand& t_command);
		inline const std::vector<RenderCommand>& getCommands() const { return m_commands; }
		void clear();

	private:
		
		// render commands
		std::vector<RenderCommand> m_commands;
	};
}