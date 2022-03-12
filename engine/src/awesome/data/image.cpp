#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Image::Image(const std::string& filename)
	: m_data()
	, m_width()
	, m_height()
	, m_channels()
{
	stbi_set_flip_vertically_on_load(1);
	m_data = std::shared_ptr<unsigned char>(stbi_load(filename.c_str(), &m_width, &m_height, &m_channels, 4));
}

Image::Image(const Image& image)
	: m_data()
	, m_width(image.m_width)
	, m_height(image.m_height)
	, m_channels(image.m_channels)
{
}

Image::~Image()
{

}

std::shared_ptr<unsigned char> Image::data() const
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

int Image::getChannels() const
{
	return m_channels;
}

Image& Image::operator=(const Image& other)
{
	m_data = other.m_data;
	m_width = other.m_width;
	m_height = other.m_height;
	m_channels = other.m_channels;
	return *this;
}

bool Image::operator==(const Image& other) const
{
	return m_data == other.m_data
		&& m_width == other.m_width
		&& m_height == other.m_height
		&& m_channels == other.m_channels;
}

bool Image::operator!=(const Image& other) const
{
	return m_data != other.m_data
		|| m_width != other.m_width
		|| m_height != other.m_height
		|| m_channels != other.m_channels;
}