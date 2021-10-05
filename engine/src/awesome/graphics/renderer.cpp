#include "renderer.h"

#include "command.h"
#include "context.h"
#include "gizmos.h"

Renderer::Renderer(Context& context)
	: backgroundColor(Color::Black)
	, m_context(context)
	, m_gizmos()
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

	std::vector<Command*> gizmosCommands = m_gizmos.commands();
	for (auto it = gizmosCommands.begin(); it != gizmosCommands.end(); ++it)
	{
		Command* const command = *it;
		command->execute(m_context);
	}
}

void Renderer::clear()
{
	m_commands.clear();
}
