#pragma once

#include <string>
#include <vector>

namespace awesome
{
	namespace data
	{
		class String
		{
		private:

			String() = default;
			~String() = default;

		public:

			String& operator=(String&& str) = delete;
			String(const String& str) = delete;
			String(String&& str) = delete;
			String& operator= (const String& str) = delete;

			static std::string ltrim(const std::string& str);
			static std::string rtrim(const std::string& str);
			static std::string trim(const std::string& str);

			static std::string lower(const std::string& str);
			static std::string upper(const std::string& str);

			static bool contains(const std::string& str, const std::string& substr);

			static std::vector<std::string> split(const std::string& str, const std::string& delimiter = " ");

			static bool isEqual(const std::string& str1, const std::string& str2, const bool ignore_case = false);
		};
	}
}