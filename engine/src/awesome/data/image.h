#pragma once

#include <string>

namespace awesome
{
	class Image final
	{
	public:

		Image(const std::string& t_filename);
		~Image();

		unsigned char* data() const;
		int getWidth() const;
		int getHeight() const;
		int getComponents() const;

	private:

		// image data
		unsigned char* m_data;
		// image width
		int m_width;
		// image height
		int m_height;
		// num of components
		int m_components;
	};
}