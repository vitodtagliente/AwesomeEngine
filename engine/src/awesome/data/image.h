/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <string>

class Image final
{
public:

	Image(const std::string& filename);
	~Image();

	unsigned char* data() const;
	int getWidth() const;
	int getHeight() const;
	int getChannels() const;

private:

	// image data
	unsigned char* m_data;
	// image width
	int m_width;
	// image height
	int m_height;
	// num of components
	int m_channels;
};