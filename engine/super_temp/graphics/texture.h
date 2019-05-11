#pragma once

#include "graphics_element.h"
#include "../core/types.h"

namespace awesome
{
	class Texture : public IGraphicsElement
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

		Texture(const unsigned char* const t_data, const uint t_width, const uint t_height,
			const uint t_components, const Options& t_options = Options{});

		inline uint getWidth() const { return m_width; }
		inline uint getHeight() const { return m_height; }

	protected:

		// texture size
		uint m_width, m_height;
		// format of the texture object
		uint m_format;
	};
}