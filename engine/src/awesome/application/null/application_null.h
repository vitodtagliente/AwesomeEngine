#pragma once

#include "../application.h"

namespace awesome
{
	class ApplicationNull final : public Application
	{
	public:

		ApplicationNull();
		virtual ~ApplicationNull() override;
	};
}