#include "archive.h"

Archive::Archive(const std::filesystem::path& filename, const Mode mode)
	: m_filename(filename)
	, m_mode(mode)
	, m_file(filename.string().c_str(), /*std::ios_base::binary |*/ (mode == Mode::Read ? std::ios_base::in : std::ios_base::out))
{
}

Archive::~Archive()
{
	m_file.close();
}

void Archive::close()
{
	m_file.close();
}
