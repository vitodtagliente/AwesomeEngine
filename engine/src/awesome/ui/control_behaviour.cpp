#include "control_behaviour.h"

#include "control.h"

ControlBehaviour::ControlBehaviour(const ControlBehaviour& other)
	: enabled(other.enabled)
{

}

bool ControlBehaviour::operator==(const ControlBehaviour& other) const
{
	return m_id == other.m_id;
}

bool ControlBehaviour::operator!=(const ControlBehaviour& other) const
{
	return m_id != other.m_id;
}

void ControlBehaviour::attach(Control* const control)
{
	m_owner = control;
}

void ControlBehaviour::detach()
{
	uninit();
	m_owner = nullptr;
}