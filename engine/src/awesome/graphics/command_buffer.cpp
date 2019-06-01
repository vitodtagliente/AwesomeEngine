#include "command_buffer.h"

namespace awesome
{
	CommandBuffer::CommandBuffer()
		: m_commands()
	{
	}

	CommandBuffer::~CommandBuffer()
	{
	}

	void CommandBuffer::sort()
	{
		// to be implemented
	}

	void CommandBuffer::push_back(const RenderCommand& t_command)
	{
		m_commands.push_back(t_command);
	}
	
	void CommandBuffer::clear()
	{
		m_commands.clear();
	}
}