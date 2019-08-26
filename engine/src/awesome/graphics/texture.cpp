#include "texture.h"

namespace awesome
{	
	Texture::Texture(const unsigned char* const t_data, const unsigned int t_width, const unsigned int t_height,
		const unsigned int t_channels, const Options& t_options /*= Options{}*/)
		: m_id(0)
		, m_width(t_width)
		, m_height(t_height)
		, m_format()
	{

	}
}