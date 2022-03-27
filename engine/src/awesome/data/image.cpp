#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Image::Image()
	: data()
	, width()
	, height()
	, channels()
{
}

Image::Image(const std::shared_ptr<unsigned char>& data, const int width, const int height, const int channels)
	: data(data)
	, width(width)
	, height(height)
	, channels(channels)
{
}

Image::Image(const Image& other)
	: data(other.data)
	, width(other.width)
	, height(other.height)
	, channels(other.channels)
{
}

Image::~Image()
{

}

Image Image::load(const std::filesystem::path& filename)
{
	stbi_set_flip_vertically_on_load(1);
	int width, height, channels;
	std::shared_ptr<unsigned char> data(stbi_load(filename.string().c_str(), &width, &height, &channels, 4));
	return Image(data, width, height, channels);
}

Image& Image::operator=(const Image& other)
{
	data = other.data;
	width = other.width;
	height = other.height;
	channels = other.channels;
	return *this;
}

bool Image::operator==(const Image& other) const
{
	return data == other.data
		&& width == other.width
		&& height == other.height
		&& channels == other.channels;
}

bool Image::operator!=(const Image& other) const
{
	return data != other.data
		|| width != other.width
		|| height != other.height
		|| channels != other.channels;
}