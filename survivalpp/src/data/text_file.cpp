#include "text_file.h"

#include <fstream>
#include <sstream>

#include "archive.h"

void TextFile::save(const std::string& data, const std::filesystem::path& path)
{
	Archive archive(path, Archive::Mode::Write);
	archive << data;
}

bool TextFile::load(const std::filesystem::path& path, std::string& data)
{
	if (std::filesystem::exists(path))
	{
		std::ostringstream buffer;
		std::ifstream input(path.c_str());
		buffer << input.rdbuf();
		return data = buffer.str(), true;
	}
	return false;
}
