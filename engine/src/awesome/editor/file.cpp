#include "file.h"

namespace editor
{
	File::File()
		: path()
		, name()
		, extension()
		, isDirectory()
	{
	}

	File::File(const std::filesystem::path& path)
		: path(path.string())
		, name(path.filename().string())
		, extension(path.extension().string())
		, isDirectory(std::filesystem::is_directory(path))
	{
	}

	File::File(const File& other)
		: path(other.path)
		, name(other.name)
		, extension(other.extension)
		, isDirectory(other.isDirectory)
	{
	}

	bool File::exists() const
	{
		if (path.empty()) return false;

		std::filesystem::path mypath(path);
		return std::filesystem::exists(path);
	}

	File& File::operator=(const File& other)
	{
		path = other.path;
		name = other.name;
		extension = other.extension;
		isDirectory = other.isDirectory;
		return *this;
	}

	bool File::operator==(const File& other) const
	{
		return path == other.path 
			&& name == other.name
			&& extension == other.extension
			&& isDirectory == other.isDirectory;
	}

	bool File::operator!=(const File& other) const
	{
		return path != other.path
			|| name != other.name
			|| extension != other.extension
			|| isDirectory != other.isDirectory;
	}
}
