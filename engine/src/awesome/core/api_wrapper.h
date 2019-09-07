#pragma once

namespace awesome
{
	class APIWrapper
	{
	public:

		APIWrapper() = default;
		virtual ~APIWrapper() = default;

		virtual bool startup() = 0;
		virtual void shutdown() = 0;
	};
}