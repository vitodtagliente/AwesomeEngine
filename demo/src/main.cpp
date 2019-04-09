/*
 * Engine examples
 * This is a test sandbox application
 */

#include <grandel/grandel.h>

// examples
#include "test_input_behaviour.h"

using namespace grandel;
using namespace examples;

int main() 
{
	const auto test_input_behaviour = new TestInputBehaviour();
	const auto properties = WindowProperties{};
	Application::run("Grandel - Demo", properties, {test_input_behaviour});
	return 0;

}