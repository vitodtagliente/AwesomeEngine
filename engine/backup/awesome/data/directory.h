/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <filesystem>

class Directory
{
public:
	struct ScanSettings
	{
		ScanSettings();
		ScanSettings(const std::string& allowedExtension, bool ignoreDirectories);

		std::string allowedExtension;
		bool ignoreDirectories;
	};

	static Directory scan(const std::filesystem::path& path, const ScanSettings& settings = {});

	bool directory(const std::filesystem::path& directory);
	void refresh();
	bool up();

	std::vector<std::filesystem::path> files;
	std::filesystem::path parent;
	std::filesystem::path path;

private:
	ScanSettings m_settings;
};