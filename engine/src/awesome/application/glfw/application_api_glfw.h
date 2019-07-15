#pragma once

#include <awesome/application/application_api.h>

namespace awesome
{
	class ApplicationAPI_GLFW : public ApplicationAPI
	{
	public:

		ApplicationAPI_GLFW()
			: ApplicationAPI(ApplicationAPI::Type::GLFW)
		{

		}
		~ApplicationAPI_GLFW() = default;

		virtual bool startup() override;
		virtual void shutdown() override;

		// create application's objects
		virtual Input* createInput() const override;
		virtual Time* createTime() const override;
		virtual Window* createWindow() const override;
	};
}