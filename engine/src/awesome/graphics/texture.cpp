#include "texture.h"

namespace awesome
{
	
	Texture::Texture(const unsigned char* const t_data, const uint t_width, const uint t_height,
		const uint t_components, const Options& t_options /* = Options */)
		: m_width(t_width)
		, m_height(t_height)
		, m_format()
	{

	}
}