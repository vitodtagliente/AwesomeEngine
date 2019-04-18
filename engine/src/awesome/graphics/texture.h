#pragma once

#include "../types.h"

namespace awesome
{
	class Texture
	{
	public:

		struct Options
		{
			Options();

			// Wrapping mode on S axis
			uint wrapS;
			// Wrapping mode on T axis 
			uint wrapT;
			// Filtering mode if texture pixels < screen pixels
			uint filterMin;
			// Filtering mode if texture pixels > screen pixels
			uint filterMax;
		};

		Texture(unsigned char * const t_data, const uint t_width, const uint t_height,
			const uint t_components, const Options& t_options = Options{});
		~Texture();

		uint id() const;
		void bind(const uint t_slot = 0);
		void unbind();

		uint getWidth() const;
		uint getHeight() const;

	private:

		// texture id
		uint m_id;
		// texture size
		uint m_width, m_height;
		// Format of texture object
		unsigned int m_format;
	};
}