#pragma once

#include "../time.h"

namespace awesome
{
	class TimeGLFW final : public Time
	{
	private:

		// return the GLFW application's time
		virtual double getTime_implementation() const override;

	};
}