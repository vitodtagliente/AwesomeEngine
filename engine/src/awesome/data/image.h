/// Copyright (c) Vito Domenico Tagliente
#pragma once

#include <memory>
#include <string>

struct Image final
{
public:
	Image();
	Image(const std::shared_ptr<unsigned char>& data, int witdh, int height, int channels);
	Image(const Image& other);
	~Image();

	static Image load(const std::string& filename);

	Image& operator= (const Image& other);
	bool operator== (const Image& other) const;
	bool operator!= (const Image& other) const;

	std::shared_ptr<unsigned char> data;
	int width;
	int height;
	int channels;
};