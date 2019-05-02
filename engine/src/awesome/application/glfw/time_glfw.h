#pragma once

#include "../time.h"

namespace awesome
{
	class TimeGLFW final : public Time
	{
	public:

		virtual bool startup() override;
		virtual void shutdown() override;

	private:

		// return the GLFW application's time
		virtual double getApplicationTime() const override;

	};
}