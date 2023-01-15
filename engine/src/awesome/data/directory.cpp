#include "directory.h"

Directory Directory::scan(const std::filesystem::path& path, const ScanSettings& settings)
{
	Directory directory;
	directory.parent = path.parent_path();
	directory.path = path;
	directory.m_settings = settings;

	if (path.empty()) return directory;

	for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		if (entry.is_directory())
		{
			if (!settings.ignoreDirectories)
			{
				directory.files.push_back(entry.path());
			}
		}
		else
		{
			if (settings.allowedExtension.empty()
				|| entry.path().extension().string() == settings.allowedExtension)
			{
				directory.files.push_back(entry.path());
			}
		}
	}

	return directory;
}
bool Directory::directory(const std::filesystem::path& directory)
{
	const auto& it = std::find(files.begin(), files.end(), directory);
	if (it != files.end())
	{
		*this = scan(directory, m_settings);
		return true;
	}
	return false;
}

void Directory::refresh()
{
	*this = scan(path, m_settings);
}

bool Directory::up()
{
	if (!parent.empty())
	{
		*this = scan(parent, m_settings);
		return true;
	}
	return false;
}

Directory::ScanSettings::ScanSettings()
	: allowedExtension()
	, ignoreDirectories(false)
{
}

Directory::ScanSettings::ScanSettings(const std::string& allowedExtension, const bool ignoreDirectories)
	: allowedExtension(allowedExtension)
	, ignoreDirectories(ignoreDirectories)
{
}
