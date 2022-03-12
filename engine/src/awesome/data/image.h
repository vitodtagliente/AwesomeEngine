/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

class Image final
{
public:
	Image(const std::string& filename);
	Image(const Image& image);
	~Image();

	std::shared_ptr<unsigned char> data() const;
	int getWidth() const;
	int getHeight() const;
	int getChannels() const;

	Image& operator= (const Image& other);
	bool operator== (const Image& other) const;
	bool operator!= (const Image& other) const;

private:

	// image data
	std::shared_ptr<unsigned char> m_data;
	// image width
	int m_width;
	// image height
	int m_height;
	// num of components
	int m_channels;
};