#pragma once

#include <initializer_list>
#include <string>

namespace awesome
{
	struct Path
	{
		Path() = delete;
		~Path() = delete;

		static std::string combine(const std::string& t_str1, const std::string& t_str2);
		static std::string combine(const std::initializer_list<std::string>& t_args);

		// return the name of the directory 
		static std::string getDirectoryName(const std::string& t_path);
		// return the extension of a path, "." included
		static std::string getExtension(const std::string& t_path);
		// return the file name plus the extension
		static std::string getFilename(const std::string& t_path, const bool t_includeExtension = true);
		// return true if the path contains an extension
		static bool hasExtension(const std::string& t_path);

		static const char directorySeparatorChar;

	};
}