#pragma once

#include "../time.h"

namespace awesome
{
	class TimeGLFW final : public Time
	{
	public:

		TimeGLFW();
		virtual ~TimeGLFW() override;

		virtual bool startup() override;
		virtual void shutdown() override;

		virtual void tick(const double t_deltaTime = 0) override;
	};
}