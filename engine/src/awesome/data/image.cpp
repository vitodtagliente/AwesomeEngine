#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace awesome
{
	Image::Image(const std::string& t_filename)
		: m_data()
		, m_width()
		, m_height()
		, m_components()
	{
		stbi_set_flip_vertically_on_load(1);
		m_data = stbi_load(t_filename.c_str(), &m_width, &m_height, &m_components, 4);
	}

	Image::~Image()
	{
		stbi_image_free(m_data);
	}

	unsigned char* Image::data() const
	{
		return m_data;
	}

	int Image::getWidth() const
	{
		return m_width;
	}

	int Image::getHeight() const
	{
		return m_height;
	}

	int Image::getComponents() const
	{
		return m_components;
	}
}