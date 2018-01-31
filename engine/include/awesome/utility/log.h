#pragma once

#include <string>

namespace Awesome
{
	namespace Utility
	{
		class Log
		{
		private:
			/* singleton pattern */
			static Log* s_instance;
			std::string filename;
			std::string current_datetime();

		public:
			bool std_output{ true };
			Log(std::string filename);
			Log(std::string filename, bool enable_std_output);

			void log(std::string message);
			void log(std::string category, std::string message);

			/* singleton pattern */
			static Log* instance();
		};
	}
}