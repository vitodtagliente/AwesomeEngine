#include "font.h"

Font::Font(const std::filesystem::path& path)
	: Asset()
{
	this->path = path;
	m_data = TTF_OpenFont(path.string().c_str(), 25);
}

Font::~Font()
{
	free();
}

void Font::free()
{
	TTF_CloseFont(m_data);
}
