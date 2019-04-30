#pragma once

#include "../application.h"

namespace awesome 
{
	class ApplicationGLFW : public Application
	{
	public:

		ApplicationGLFW();
		virtual ~ApplicationGLFW() override;
		
		virtual bool startup() override;
		virtual void shutdown() override;

	};
}