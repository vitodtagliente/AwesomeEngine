#include "input_device.h"

#include "input_system.h"

namespace awesome
{
	InputDevice::InputDevice(InputSystem* const t_inputSystem, const Type t_type /*= Type::Unknown*/)
		: m_inputSystem(t_inputSystem)
		, m_type(t_type)
	{

	}
}