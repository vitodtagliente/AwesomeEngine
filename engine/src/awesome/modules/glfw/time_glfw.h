#pragma once

#include <awesome/application/time.h>

namespace awesome
{
	class TimeGLFW final : public Time
	{
	private:

		// return the GLFW application's time
		virtual double getTime_implementation() const override;

	};
}