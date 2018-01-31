#include <awesome/utility/log.h>
#include <iostream>
#include <fstream>
#include <ctime>

namespace Awesome
{
	namespace Utility
	{
		Log* Log::s_instance = nullptr;

		std::string Log::current_datetime()
		{
			time_t     now = time(0);
			struct tm  tstruct;
			char       buf[80];
			tstruct = *localtime(&now);
			// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
			// for more information about date/time format
			strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

			return buf;
		}

		Log* Log::instance() {
			if (s_instance == nullptr)
				s_instance = new Log("log.txt"); 
			return s_instance;
		}

		Log::Log(std::string filename)
		{
			if (s_instance == nullptr)
				s_instance = this;

			this->filename = filename;
		}
		
		Log::Log(std::string filename, bool enable_std_output)
		{
			if (s_instance == nullptr)
				s_instance = this;

			std_output = enable_std_output;
			this->filename = filename;
		}
		
		void Log::log(std::string message)
		{
			if (std_output)
				std::cout << message << std::endl;

			std::ofstream file{ filename, std::ios_base::app };
			if (file.is_open()) {
				std::string line{ "[" + current_datetime() + "] " + message + "\n" };
				file << line;
			}
			file.close();
		}

		void Log::log(std::string category, std::string message)
		{
			log(category + ": " + message);
		}
	}
}