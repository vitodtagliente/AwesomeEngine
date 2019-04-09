#pragma once

#include <string>

namespace awesome
{
	enum class ModuleStartupResult
	{
		Success,
		Error,
		FatalError
	};

	class ApplicationModule
	{
	protected:

		std::string m_ErrorMessage{};

	public:

		ApplicationModule() = default;
		virtual ~ApplicationModule() = default;

		ApplicationModule& operator=(ApplicationModule&& application_module) = delete;
		ApplicationModule(const ApplicationModule& application_module) = delete;
		ApplicationModule(ApplicationModule&& application_module) = delete;
		ApplicationModule& operator= (const ApplicationModule& application_module) = delete;

		virtual void init() = 0;
		virtual ModuleStartupResult startup() = 0;
		virtual void shutdown() = 0;

		inline const std::string& getErrorMessage() const { return m_ErrorMessage; }
	};
}