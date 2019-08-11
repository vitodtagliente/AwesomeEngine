#pragma once

#include <string>
#include <vector>

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

	struct Directory
	{
		Directory() = delete;
		~Directory() = delete;
		
		// create a directory 
		static bool create(const std::string& t_name);
		static std::vector<std::string> getDirectories(const std::string& t_path);
		static std::vector<std::string> getFiles(const std::string& t_path);
		// return true if the directory exists
		static bool exists(const std::string& t_path);
		// retrieve the current working directory
		static std::string getCurrentDirectory();

	};

	class File
	{

	};
}