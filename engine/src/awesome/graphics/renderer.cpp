#include "renderer.h"

#include "command.h"
#include "context.h"
#include "gizmos.h"

Renderer::Renderer(Context& context)
	: backgroundColor(Color::Black)
	, m_context(context)
	, m_commands()
{
}

void Renderer::begin()
{
	m_context.clear(backgroundColor);
	Gizmos::instance()->clear();
}

void Renderer::flush()
{
	for (auto it = m_commands.begin(); it != m_commands.end(); ++it)
	{
		Command* const command = *it;
		command->execute(m_context);
	}

	std::vector<Command*> gizomsCommands = Gizmos::instance()->commands();
	for (auto it = gizomsCommands.begin(); it != gizomsCommands.end(); ++it)
	{
		Command* const command = *it;
		command->execute(m_context);
	}
}

void Renderer::clear()
{
	m_commands.clear();
}
