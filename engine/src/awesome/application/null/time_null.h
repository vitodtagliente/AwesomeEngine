#pragma once

#include "../time.h"

namespace awesome
{
	class TimeNULL final : public Time
	{
	private:

		// return the GLFW application's time
		virtual double getApplicationTime() const override;

	};
}